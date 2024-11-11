/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:40:31 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/11 19:33:08 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// NEED TO WRITE FREE FOR COMMANDS AND OPERATORS
// NEED TO CONNECT ALL FREE FUNCTIONS

void	free_cmd(t_command *cmd)
{
	t_outfile	*tmp;
	t_outfile	*next;

	tmp = NULL;
	next = NULL;
	if (!cmd)
		return ;
	if (cmd->word)
		free(cmd->word);
	if (cmd->args)
		ft_mtx_free(cmd->args);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfiles)
	{
		tmp = cmd->outfiles;
		while (tmp)
		{
			next = tmp->next;
			free(tmp->name);
			free(tmp);
			tmp = next;
		}
	}
	free(cmd);
}

void	free_tree(void *root)
{
	t_command	*cmd;
	t_operator	*op;

	if (!root)
		return ;
	cmd = (t_command *)root;
	op = (t_operator *)root;
	if (cmd->type == COMMAND_ID || cmd->type == EXE_ID)
		free_cmd(cmd);
	else
	{
		free_tree(op->left);
		free_tree(op->right);
		free(op);
	}
}
