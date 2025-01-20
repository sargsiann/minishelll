/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:17:39 by dasargsy          #+#    #+#             */
/*   Updated: 2025/01/20 15:58:25 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_matrix(char **mtx)
{
	int	i;

	i = 0;
	if (!mtx)
		return ;
	while (mtx[i])
	{
		printf("[%s]\n", mtx[i]);
		i++;
	}
}

void	print_tokens(t_token **token)
{
	t_token	*tmp;

	if (!token || !*token)
		return ;
	tmp = *token;
	while (tmp)
	{
		printf("____________________\n");
		printf("word: [%s]\n", tmp->word);
		printf("type: %d\n", tmp->type);
		printf("____________________\n");
		tmp = tmp->next;
	}
}

void	print_vars(t_var *head)
{
	t_var	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("____________________\n");
		printf("key: %s			", tmp->key);
		printf("value: %s\n", tmp->value);
		tmp = tmp->next;
		printf("____________________\n");
	}
}


void	print_node(void *node)
{
	t_command	*cmd;
	t_operator	*op;

	if (!node)
		return ;
	cmd = (t_command *)node;
	op = (t_operator *)node;
	if (cmd->type == COMMAND_ID || cmd->type == EXE_ID)
	{
		printf("%s", cmd->word);
		printf(" args= ");
		for (int i = 0; cmd->args[i]; i++)
		{
			printf("%s ", cmd->args[i]);
		}
		if (cmd->infile)
			printf("infile = %s ", cmd->infile);
		if (cmd->here_doc)
		{
			printf("here_doc= ");
			for (int i = 0; cmd->here_doc[i]; i++)
			{
				printf("%s ", cmd->here_doc[i]);
			}
		}
		if (cmd->outfiles)
		{
			t_outfile	*tmp;

			tmp = cmd->outfiles;
			printf("outfiles = ");
			while (tmp)
			{
				printf("%s ", tmp->name);
				tmp = tmp->next;
			}
		}
	}
	else
	{
		if (op->type == PIPE_ID)
			printf("|\n");
		if (op->type == AND_ID)
			printf("&&\n");
		if (op->type == OR_ID)
			printf("||\n");
	}
}

void	print_tree(void *tree, int level)
{
	t_operator	*op;
	t_command	*cmd;

	op = (t_operator *)tree;
	cmd = (t_command *)tree;
	for (int i = 0; i < level; i++)
		printf("|   ");
	printf("|-- ");
	print_node(cmd);
	printf("\n");
	if (cmd && cmd->type != COMMAND_ID && cmd->type != EXE_ID)
	{
		print_tree(op->left, level + 1);
		print_tree(op->right, level + 1);
	}
}
