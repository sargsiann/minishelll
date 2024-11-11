/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:17:39 by dasargsy          #+#    #+#             */
/*   Updated: 2024/09/11 15:25:50 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_matrix(char **mtx)
{
	int	i;

	i = 0;
	if (!mtx)
		return ;
	while (mtx[i])
	{
		printf("%s\n", mtx[i]);
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
