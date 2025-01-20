/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:44:24 by dasargsy          #+#    #+#             */
/*   Updated: 2025/01/20 16:16:58 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_in_quotes(char *str, char quote, int index)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (index == 0)
		return (0);
	while (i < index)
	{
		if (str[i] == quote)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (0);
	return (1);
}

int	is_double_one_quote(char *str, int index)
{
	int	i;
	int count;

	i = index;
	count = 0;
	while (str[i])
	{
		if (str[i] == 39)
			count++;
		i++;
	}
	if (count == 1)
		return (0);
	return (1);
}

int	is_expansable(t_token *token, char c)
{
	char	*str;
	size_t	i;

	str = token->word;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{		
		if (str[i] == c && !
		is_in_quotes(str, 39, i) && !is_in_quotes(str, 34, i))
			return (1);
		i++;
	}
	return (0);
}

void	expansion(t_token **head, char **envp)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == DELIMITER_ID)
			tmp = tmp->next;
		if (tmp->type == COMMAND_ID && ft_strcmp(tmp->word,"awk") == 0)
		{
			tmp = tmp->next;
			while (tmp && tmp->type != COMMAND_ID)
				tmp = tmp->next;	
		}
		if (!tmp )
			break ;
		if (!tmp->word)
			tmp = tmp->next;
		if (is_expansable(tmp, '*'))
			expand_wildcart(&tmp);
		expand_var(&tmp, envp);
		if (has_quotes(tmp->word))
			expand_quotes(&tmp, has_quotes(tmp->word));
		tmp = tmp->next;
	}
}
