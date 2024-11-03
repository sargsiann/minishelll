/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:47:54 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/03 17:41:45 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

void	exec_cmd(t_command *cmd)
{
	int			pid;
	int			status;
	int			fd;
	t_outfile	*tmp;

	pid = fork();
	if (pid == 0)
	{
		if (cmd->infile)
		{
			fd = open(cmd->infile, O_RDONLY);
			if (fd < 0)
				ft_error(cmd->infile, NO_FILE_STATUS);
			dup2(fd, 0);
			close(fd);
		}
		if (cmd->outfiles)
		{
			while (tmp)
			{
				if (tmp->type == OUTFILE_ID)
					fd = open(tmp->name, O_WRONLY | O_CREAT, O_APPEND | 0644);
				else
					fd = open(tmp->name, O_WRONLY | O_CREAT, O_TRUNC | 0644);
				if (fd < 0)
					ft_error(tmp->name, NO_FILE_STATUS);
				if (tmp->next == NULL)
					dup2(fd, 1);
				close(fd);
				tmp = tmp->next;
			}
			dup2(fd, 1);
			close(fd);
		}
		if (execve(cmd->args[0], cmd->args, NULL) < 0)
			ft_error(cmd->args[0], COMMAND_NOT_FOUND_STATUS);
	}
	else
	{
		waitpid(pid, &status, 0);
		g_status = WEXITSTATUS(status);
	}
}

void	execution(void *root)
{
	t_command	*cmd;
	t_operator	*op;
	int			fd[2];
	int			pid;

	op = (t_operator *)root;
	if (op->type == COMMAND_ID)
	{
		cmd = (t_command *)op;
		if (cmd->args)
			exec_cmd(cmd);
	}
	else
	{
		execution(op->left);
		execution(op->right);
	}
	if (op->type == PIPE_ID)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			execution(op->left);
			exit(0);
		}
		else
		{
			waitpid(pid, NULL, 0);
			dup2(fd[0], 0);
			close(fd[1]);
			execution(op->right);
		}
	}
	if (op->type == OR_ID)
	{
		if (g_status != 0)
			execution(op->right);
	}
	if (op->type == AND_ID)
	{
		if (g_status == 0)
			execution(op->right);
	}
}
