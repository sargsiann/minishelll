/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:47:54 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/23 20:56:16 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

static	int	is_op(int n)
{
	if (n == PIPE_ID || n == AND_ID || n == OR_ID)
		return (1);
	return (0);
}

// NEED TO WRITE PIPE CASE
// OR CASE
// AND CASE
// COMMAND EXEC

void	execution(void *root, int fd[2], char **envp)
{
	t_operator	*op;
	t_command	*com;
	pid_t		pid;

	op = root;
	com = root;
	if (!is_op(op->type))
	{
		pid = fork();
		if (pid == 0)
			command_execution(com, fd[0], fd[1], envp);
		waitpid(pid, &g_status, 0);
	}
	else
	{
		if (op->type == PIPE_ID)
		{
			printf("PIPE\n");
			pipe(fd);
			execution(op->left, fd, envp);
			execution(op->right, fd, envp);
		}
		else if (op->type == AND_ID)
		{
			execution(op->left, fd, envp);
			if (g_status == 0)
				execution(op->right, fd, envp);
		}
		else if (op->type == OR_ID)
		{
			execution(op->left, fd, envp);
			if (g_status != 0)
				execution(op->right, fd, envp);
		}
	}
}