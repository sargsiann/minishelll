/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:00:07 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/03 19:31:14 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_command	*new_command(t_token *t, char **envp)
{
	t_command	*command;

	(void )envp;
	command = malloc(sizeof(t_command));
	command->type = COMMAND_ID;
	if (t->type == EXE_ID)
		command->word = ft_strdup("/usr/bin/bash");
	else if (ft_strcmp(t->word, "unset") == 0
		|| ft_strcmp(t->word, "export") == 0
		|| ft_strcmp(t->word, "cd") == 0
		|| ft_strcmp(t->word, "env") == 0 || ft_strcmp(t->word, "exit") == 0)
		command->word = ft_strdup(t->word);
	else
		command->word = get_command_path(envp, t->word);
	command->args = get_cmd_args(t);
	command->infile = get_cmd_infile(t->next);
	command->here_doc = get_here_doc(t->next);
	command->outfiles = get_cmd_outfiles(t->next);
	return (command);
}

t_operator	*new_operator(t_token *t, int priority)
{
	t_operator	*op;

	op = malloc(sizeof(t_operator));
	op->type = t->type;
	op->priority = priority;
	op->left = NULL;
	op->right = NULL;
	return (op);
}

void	add_node(t_operator *op, void *node, int direction)
{
	t_command	*cmd;

	cmd = (t_command *)node;
	if (cmd->type == COMMAND_ID || cmd->type == EXE_ID)
	{
		if (direction == 0)
			op->left = (t_command *)node;
		else
			op->right = (t_command *)node;
	}
	else
	{
		if (direction == 0)
			op->left = (t_operator *)node;
		else
		{
			op->right = (t_operator *)node;
		}
	}
}

t_outfile	*new_outfile(t_token *command)
{
	t_outfile	*outfile;

	outfile = malloc(sizeof(t_outfile));
	outfile->name = ft_strdup(command->word);
	outfile->type = command->type;
	outfile->next = NULL;
	return (outfile);
}
