/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:47:54 by dasargsy          #+#    #+#             */
/*   Updated: 2025/01/21 00:05:02 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

extern int g_status; // Global status variable to track command success

int	is_op(void *op);

int is_op(void *op) {
    int type = ((t_operator *)op)->type;
    return (type == PIPE_ID || type == AND_ID || type == OR_ID);
}

// Function to execute a command
void execute_command(t_command *cmd, char ***envp) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        if (cmd->infile) {
            int fd_in = open(cmd->infile, O_RDONLY);
            if (fd_in < 0) {
                perror("open infile");
                exit(EXIT_FAILURE);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }

        // Handle output redirection
        if (cmd->outfiles) {
            t_outfile *out = cmd->outfiles;
            while (out) {
                int fd_out = open(out->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd_out < 0) {
                    perror("open outfile");
                    exit(EXIT_FAILURE);
                }
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
                out = out->next;
            }
        }

        // Execute the command
        execve(cmd->word, cmd->args, *envp);
        perror("execve failed");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork failed");
    } else {
        // Parent process
        waitpid(pid, &g_status, 0);
        if (WIFEXITED(g_status)) {
            g_status = WEXITSTATUS(g_status);
        }
    }
}

// Function to execute a pipe
void execute_pipe(t_operator *op, char ***envp) {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }
    pid_t left_pid = fork();
    if (left_pid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO); 
        close(fd[1]);

        if (is_op(op->left)) {
            execute_pipe((t_operator *)op->left, envp);
        } else {
            execute_command((t_command *)op->left, envp);
        }
        exit(EXIT_SUCCESS);     
		} else if (left_pid < 0) {
        perror("fork failed for left command");
        exit(EXIT_FAILURE);
    }

    pid_t right_pid = fork();
    if (right_pid == 0) {
        close(fd[1]); // Close write end
 		dup2(fd[0], STDIN_FILENO); // Redirect stdin to pipe
        close(fd[0]); // Close read end after redirecting

        // Execute right command
        if (is_op(op->right)) {
            execute_pipe((t_operator *)op->right, envp);
        } else {
            execute_command((t_command *)op->right, envp);
        }
        exit(EXIT_SUCCESS); // Exit child process
    } else if (right_pid < 0) {
        perror("fork failed for right command");
        exit(EXIT_FAILURE);
    }

    close(fd[0]); // Close read end
    close(fd[1]); // Close write end
    waitpid(left_pid, NULL, 0); // Wait for left command
    waitpid(right_pid, NULL, 0); // Wait for right command
}

// Main execution function
void execution(void *root, char ***envp) {
    t_operator *op = (t_operator *)root;
    t_command *com = (t_command *)root;

    if (!root) return;

    if (!is_op(op)) { // If it's a command, not an operator
        execute_command(com, envp);
    } else {
        if (op->type == PIPE_ID) { // If it's a pipe operator
            execute_pipe(op, envp);
        } else if (op->type == AND_ID) { // If it's an AND operator
            execution(op->left, envp);
            if (g_status == 0) {
                execution(op->right, envp);
            }
        } else if (op->type == OR_ID) { // If it's an OR operator
            execution(op->left, envp);
            if (g_status != 0) {
                execution(op->right, envp);
            }
        }
    }
}