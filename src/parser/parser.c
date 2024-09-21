/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:53:58 by dasargsy          #+#    #+#             */
/*   Updated: 2024/09/15 23:43:05 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// TO DO WRITE PARSE->SUBSHELL
// TO DO WRITE ADD->SUBSHELL
// TO DO WRITE MAIN FUNCTION AND SHIFTER FOR TOKEN POINTER FOR DEEPANCE

void	print_tree(void *tree, int lvl);


int		get_priority(t_token *t)
{
	if (t->type == PIPE_ID)
		return (PIPE_PR);
	if (t->type == AND_ID)
		return (AND_PR);
	if (t->type == OR_ID)
		return (OR_PR);
	return (CM_PR);
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
		printf("%s\n", cmd->word);
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

int		check_by_root(void *root, t_operator *op)
{
	t_operator	*tmp;

	tmp = (t_operator *)root;
	if (tmp->priority <= op->priority)
		return (1);
	return (0);
}

t_token *move_token(t_token *tmp, int lvl)
{
	while (1)
	{
		if (tmp->type == CLOSE_BRACE_ID)
			break;
		tmp = tmp->next;
	}
	return (tmp);
}

void	*get_tree(t_token *tmp, char **envp, int lvl)
{
	void		*root;
	t_operator	*current_op;
	t_command	*current_cmd;
	t_operator	*tmp1;

	root = NULL;
	current_cmd = NULL;
	current_op = NULL;
	while (tmp)
	{
		if (tmp->type == OPEN_BRACE_ID)
		{
			if (root == NULL)
				root = get_tree(tmp->next, envp, lvl + 1);
			else
				current_op->right = get_tree(tmp->next, envp, lvl + 1);
			tmp = move_token(tmp->next, lvl + 1);
		}
		if (tmp->type == CLOSE_BRACE_ID && lvl != 0)
			return (root);
		if (tmp->type == COMMAND_ID || tmp->type == EXE_ID)
		{
			current_cmd = new_command(tmp, envp);
			if (root == NULL)
				root = current_cmd;
			else if (current_op)
			{
				if (current_op->left == NULL)
					add_node(current_op, current_cmd, 0);
				else
					add_node(current_op, current_cmd, 1);
			}
		}
		if (tmp->type == PIPE_ID || tmp->type == AND_ID 
			|| tmp->type == OR_ID)
		{
			tmp1 = new_operator(tmp, get_priority(tmp));
			if (current_op == NULL)
			{
				root = tmp1;
				tmp1->left = current_cmd;
				current_op = tmp1;
			}
			else
			{
				if (get_priority(tmp) < current_op->priority)
				{
					current_op->right = tmp1;
					tmp1->head = current_op;
					tmp1->left = current_cmd;
					current_op = tmp1;
				}
				else if (get_priority(tmp) == current_op->priority)
				{
					if (check_by_root(root, tmp1))
					{
						tmp1->left = root;
						root = tmp1;
						current_op = tmp1;
					}
					else
					{
						tmp1->left = current_op;
						tmp1->head = current_op->head;
						current_op->head->right = tmp1;
						current_op = tmp1;
					}
				}
				else
				{
					tmp1->left = root;
					root = tmp1;
					current_op = tmp1;
				}
			}
		}
		tmp = tmp->next;
	}
	print_tree(root, 1);
	return (root);
}

void print_tree(void *tree, int level) {
    t_operator *op;
    t_command *cmd;

    op = (t_operator *)tree;
    cmd = (t_command *)tree;

    // Печать отступов и маркеров для отображения уровня
    for (int i = 0; i < level; i++) {
        printf("|   ");
    }

    // Печать текущего узла
    printf("|-- ");
    print_node(cmd);
    printf("\n");

    // Рекурсивный вызов для операторов
    if (cmd && cmd->type != COMMAND_ID && cmd->type != EXE_ID) {
        print_tree(op->left, level + 1);
        print_tree(op->right, level + 1);
    }
}
