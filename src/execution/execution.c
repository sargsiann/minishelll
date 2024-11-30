/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:47:54 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/30 14:35:24 by dasargsy         ###   ########.fr       */
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

void	execution(void *root, char ***envp)
{
	t_operator	*op;
	t_command	*com;
	int			fd[2];

	op = root;
	com = root;
	fd[0] = -1;
	fd[1] = -1;
	if (!is_op(op->type))
		command_execution(com, fd[0], fd[1], envp);
	else
	{
		if (op->type == PIPE_ID)
		{
			pipe(fd);
			execution(op->left, envp);
			execution(op->right, envp);
		}
		else if (op->type == AND_ID)
		{
			execution(op->left, envp);
			if (g_status == 0)
				execution(op->right, envp);
		}
		else if (op->type == OR_ID)
		{
			execution(op->left, envp);
			if (g_status != 0)
				execution(op->right, envp);
		}
	}
}