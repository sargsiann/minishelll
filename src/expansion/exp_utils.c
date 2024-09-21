/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:46:36 by dasargsy          #+#    #+#             */
/*   Updated: 2024/09/14 15:40:28 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_indx(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

t_var	*var_new(char *key, char *value)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->key = ft_strdup(key);
	free(key);
	var->value = ft_strdup(value);
	free(value);
	var->next = NULL;
	return (var);
}

void	var_add(t_var **head, t_var *var)
{
	t_var	*tmp;

	tmp = NULL;
	if (!head || !var)
		return ;
	if (!*head)
	{
		*head = var;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = var;
}

void	free_vars(t_var **head)
{
	t_var	*tmp;

	if (!head || !*head)
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

t_var	*get_vars(char **envp)
{
	t_var	*head;
	t_var	*tmp;
	int		i;

	head = malloc(sizeof(t_var));
	i = 0;
	tmp = NULL;
	head->key = ft_substr(envp[i], 0, find_indx(envp[i], '='));
	head->value = ft_strdup(envp[i] + find_indx(envp[i], '=') + 1);
	head->next = NULL;
	while (envp[i])
	{
		tmp = var_new(ft_substr(envp[i], 0, find_indx(envp[i], '=')),
				ft_strdup(envp[i] + find_indx(envp[i], '=') + 1));
		var_add(&head, tmp);
		i++;
	}
	return (head);
}
