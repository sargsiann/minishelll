/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:10:40 by dasargsy          #+#    #+#             */
/*   Updated: 2025/01/20 16:16:49 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_priority(t_token *t)
{
	if (t->type == PIPE_ID)
		return (PIPE_PR);
	if (t->type == AND_ID)
		return (AND_PR);
	if (t->type == OR_ID)
		return (OR_PR);
	return (CM_PR);
}

int	check_by_root(void *root, t_operator *op)
{
	t_operator	*tmp;

	tmp = (t_operator *)root;
	if (tmp->priority <= op->priority)
		return (1);
	return (0);
}

t_command	*command_case(t_operator **current_op,
	void	**root, t_token *tmp, char **envp)
{
	t_command	*current_cmd;

	current_cmd = new_command(tmp, envp);
	if (!current_cmd)
		return (NULL);
	if (*root == NULL)
		*root = current_cmd;
	else if (*current_op)
	{
		if ((*current_op)->left == NULL)
			add_node(*current_op, current_cmd, 0);
		else
			add_node(*current_op, current_cmd, 1);
	}
	return (current_cmd);
}

void	operator_case(void	**root, t_token *tmp,
	t_command **current_cmd, t_operator **current_op)
{
	t_operator	*tmp1;

	tmp1 = new_operator(tmp, get_priority(tmp));
	if (*current_op == NULL)
	{
		*root = tmp1;
		tmp1->left = *current_cmd;
		*current_op = tmp1;
	}
	else
	{
		if (get_priority(tmp) < (*current_op)->priority)
		{
			(*current_op)->right = tmp1;
			tmp1->head = *current_op;
			tmp1->left = *current_cmd;
			*current_op = tmp1;
		}
		else
			mos_priority_op(root, tmp, current_op);
	}
}

void	mos_priority_op(void	**root, t_token *tmp,
	t_operator **current_op)
{
	t_operator	*tmp1;

	tmp1 = new_operator(tmp, get_priority(tmp));
	if (get_priority(tmp) == (*current_op)->priority)
	{
		if (check_by_root(*root, tmp1))
		{
			tmp1->left = *root;
			*root = tmp1;
			*current_op = tmp1;
		}
		else
		{
			tmp1->left = *current_op;
			tmp1->head = (*current_op)->head;
			(*current_op)->head->right = tmp1;
			*current_op = tmp1;
		}
	}
	else
	{
		tmp1->left = *root;
		*root = tmp1;
		*current_op = tmp1;
	}
}
