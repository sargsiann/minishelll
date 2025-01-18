/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:54:53 by dasargsy          #+#    #+#             */
/*   Updated: 2025/01/19 01:52:48 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/stat.h>

extern int	g_status;
void	pwd();
void	echo(char **args);

void	exit_with_error(const char *msg, int status)
{
	write(2, msg, strlen(msg));
	write(2, "\n", 1);
	exit(status);
}

void	check_command_path(const char *path)
{
	int			fd;
	struct stat	file_stat;
	
	if (path[0] == '.' || path[0] == '/')
	{
		if (stat(path, &file_stat) == -1)
			exit_with_error("minishell: No such file or directory", 127);
		if (S_ISDIR(file_stat.st_mode))
			exit_with_error("minishell: Is a directory", 126);
		if (access(path, X_OK) == -1)
			exit_with_error("minishell: Permission denied", 126);
	}
	else
		exit_with_error("minishell: command not found", 127);
}

void	main_exec(t_command *command, char **envp)
{
	if (command->word == NULL)
		exit(0);
	execve(command->word, &command->args[0], envp);
	check_command_path(command->word);
}

static void	ft_err(char *file, int filetype)
{
	if (access(file, F_OK) == -1)
		ft_error(NO_FILE, NO_FILE_STATUS);
	else if (access(file, R_OK) == -1 && filetype == 1)
		ft_error(NO_FILE3, NO_FILE3_STATUS);
	else if (access(file, W_OK) == -1 && filetype == 2)
		ft_error(NO_FILE3, NO_FILE3_STATUS);
	else if (access(file, X_OK) == -1 && filetype == 3)
		ft_error(NO_FILE3, NO_FILE3_STATUS);
	else
		return ;
	exit(1);
}

void	get_from_infile(char *infile)
{
	int	fd;

	if (!infile)
		return ;
	ft_err(infile, 1);
	fd = open(infile, O_RDONLY);
	dup2(fd, 0);
	close(fd);
}

void	put_to_outfile(t_outfile *outfiles)
{
	t_outfile	*tmp;
	int			fd;

	tmp = outfiles;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->type == APPENDFILE_ID)
			fd = open(tmp->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tmp->type == OUTFILE_ID)
			fd = open(tmp->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		ft_err(tmp->name, 2);
		if (tmp->next == NULL)
			dup2(fd, STDOUT_FILENO);
		close(fd);
		tmp = tmp->next;
	}
}

void	duping_inpipe(int in)
{
	if (dup2(in, STDIN_FILENO) == -1)
		ft_error("dup2 error", 1);
	close(in);
}


void	duping_outpipe(int out)
{
	if (dup2(out, STDOUT_FILENO) == -1)
		ft_error("dup2 error", 1);
	close(out);
}

int 	is_digital(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}


void	command_execution(t_command *command, int in, int out, char ***envp)
{
	int	pid;
	int	fd;
	int	fd2;
	int	i;

	if (ft_strcmp(command->word, "unset") == 0)
	{
		if (in == -1 && out == -1) 
			*envp = unset(envp, command->args[1]);
		else
			ft_error("", 1);
	}
	else if (ft_strcmp(command->word, "export") == 0)
	{
		if (in != -1 || out != -1)
		{
			ft_error("", 1);
			return ;
		}
		i = 1;
		while (command->args[i])
			*envp = export(envp, command->args[i++]);
	}
	else if (ft_strcmp(command->word, "cd") == 0)
	{
		if (command->args[2])
		{
			ft_error("cd: too many arguments", 1);
			return ;
		}
		cd(command->args[1], envp);
	}
	else if (ft_strcmp(command->word, "exit") == 0)
	{
		if (check_exit_args(command->args) == 2)
		{
			ft_error("exit: too many arguments", 1);
			exit(1);
		}
		if (check_exit_args(command->args) == 1)
		{
			ft_error("exit: numeric argument required", 1);
			exit(2);
		}
		exit(ft_atoi(command->args[1]));
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (command->here_doc)
			{
				fd = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
				get_from_hdoc(command->here_doc, fd);
				close(fd);
				fd = open("tmp", O_RDONLY);
				dup2(fd, STDIN_FILENO);
				close(fd);
				unlink("tmp");
			}
			if (command->infile)
				get_from_infile(command->infile);
			if (command->outfiles)
				put_to_outfile(command->outfiles);
			if (in != -1 && command->infile == NULL)
				duping_inpipe(in);
			if (out != -1 && command->outfiles == NULL)
				duping_outpipe(out);
			if (ft_strcmp(command->word, "env") == 0)
				env(*envp);
			if (ft_strcmp(command->word, "pwd") == 0)
				pwd();
			if (ft_strcmp(command->word, "echo") == 0)
				echo(command->args);
			main_exec(command, *envp);
		}
		close(in);
		close(out);
		if (ft_strcmp(command->word, "sleep") == 0 || out == -1)
			waitpid(pid, &g_status, 0);
	}
}
