/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:47:54 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/23 18:57:41 by dasargsy         ###   ########.fr       */
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

void	execution(void	*root)
{
	t_operator	*op;
	t_command	*com;
	pid_t		pid;
	int			fd[2];

	op = root;
	com = root;
	(void )fd[2];
	if (!is_op(op->type))
	{
		pid = fork();
		if (pid == 0)
			command_execution(com, -1, -1);
		waitpid(pid, &g_status, 0);
	}
}