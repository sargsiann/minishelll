/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:54:53 by dasargsy          #+#    #+#             */
/*   Updated: 2025/01/16 01:11:04 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;
void	pwd();
void	echo(char **args);

void	main_exec(t_command *command, char **envp)
{
	execve(command->word, &command->args[0], envp);
	ft_error(UNKNOWN_COMMAND, COMMAND_NOT_FOUND_STATUS);
	exit(1);
}

static void	ft_err(char *file, int filetype)
{
	if (access(file, F_OK) == -1)
		ft_error(NO_FILE, NO_FILE_STATUS);
	if (access(file, R_OK) == -1 && filetype == 1)
		ft_error(NO_FILE3, NO_FILE3_STATUS);
	if (access(file, W_OK) == -1 && filetype == 2)
		ft_error(NO_FILE3, NO_FILE3_STATUS);
	if (access(file, X_OK) == -1 && filetype == 3)
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
	if (fd == -1)
	{
		ft_error(NO_FILE, 1);
		exit(1);
	}
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
		ft_err(tmp->name, 2);
		if (tmp->type == APPENDFILE_ID)
			fd = open(tmp->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(tmp->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			ft_err(NO_FILE, NO_FILE_STATUS);
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

// void	change_g_status(int status, char ***envp)
// {
// 	if (WIFEXITED(status))
// 		g_status = WEXITSTATUS(status);
// 	else if (WIFSIGNALED(status))
// 		g_status = WTERMSIG(status) + 128;
// }


void	command_execution(t_command *command, int in, int out, char ***envp)
{
	int	pid;
	int	fd;
	int	fd2;
	int	i;

	if (!command->word)
	{
		ft_error(UNKNOWN_COMMAND, COMMAND_NOT_FOUND_STATUS);
		return ;
	}
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
