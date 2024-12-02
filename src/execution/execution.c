/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:47:54 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/02 18:54:16 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

static int	is_op(int type)
{
	return (type == PIPE_ID || type == AND_ID || type == OR_ID);
}

void	execute_pipe(int in_fd, t_operator *op)
{
	pid_t		pid;
	t_operator	*right;
	int			fd[2];

	if (pipe(fd) == -1)
		ft_error("Pipe error", 1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (in_fd != -1)
		{
			dup2(in_fd, 0);
			close(in_fd);
		}
		if (op->type == PIPE_ID)
			command_execution((t_command *)op->right, in_fd, fd[1], NULL);
		else if (op->type == COMMAND_ID)
			command_execution((t_command *)op, in_fd, -1, NULL);
	}
	else
	{
		close(fd[1]);
		if (op->left)
			execute_pipe(fd[0], op->left);
		else
		{
			close(in_fd);
			close(fd[0]);
			waitpid(pid, &g_status, 0);
		}
	}
}



// Основная функция для выполнения команд с пайпами
void execution(void *root, char ***envp, int *fd)
{
    t_operator *op;
    t_command *com;
	pid_t pid;

    op = root;
    com = root;

    if (!is_op(op->type)) // Если это команда, а не оператор
    {
		pid = fork();
		if (pid == 0)
			command_execution(com, fd[0], fd[1], envp);
		waitpid(pid, &g_status, 0);
	}
    else
    {
		if (op->type == PIPE_ID) // Если это оператор пайпа (|)
			execute_pipe(-1, op);
        if (op->type == AND_ID) // Если это оператор И (&&)
        {
            execution(op->left, envp, fd);
            if (g_status == 0)
                execution(op->right, envp, fd);
        }
        else if (op->type == OR_ID) // Если это оператор ИЛИ (||)
        {
            execution(op->left, envp, fd);
            if (g_status != 0)
                execution(op->right, envp, fd);
        }
    }
}
