/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:53:58 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/08 13:44:17 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tree(void *tree, int lvl);

t_token	*move_token(t_token *tmp)
{
	while (1)
	{
		if (tmp->type == CLOSE_BRACE_ID)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

static void	init(void **root, t_operator **op, t_command **com)
{
	*root = 0;
	*op = 0;
	*com = 0;
}

void	*get_tree(t_token *tmp, char **envp, int lvl)
{
	void		*root;
	t_operator	*current_op;
	t_command	*current_cmd;

	init(&root, &current_op, &current_cmd);
	while (tmp)
	{
		if (tmp->type == OPEN_BRACE_ID)
		{
			if (root == NULL)
				root = get_tree(tmp->next, envp, lvl + 1);
			else
				current_op->right = get_tree(tmp->next, envp, lvl + 1);
			tmp = move_token(tmp->next);
		}
		if (tmp->type == CLOSE_BRACE_ID && lvl != 0)
			return (root);
		if (tmp->type == COMMAND_ID || tmp->type == EXE_ID)
			current_cmd = command_case(&current_op, &root, tmp, envp);
		if (tmp->type == PIPE_ID || tmp->type == AND_ID || tmp->type == OR_ID)
			operator_case(&root, tmp, &current_cmd, &current_op);
		tmp = tmp->next;
	}
	return (root);
}
