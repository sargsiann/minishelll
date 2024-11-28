/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 01:44:24 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/28 18:54:27 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_in_quotes(char *str, char quote, int index)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
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

int	is_expansable(t_token *token, char c)
{
	char	*str;
	size_t	i;

	str = token->word;
	i = 0;
	if (str[0] == c)
		return (1);
	while (str[i])
	{
		if (str[i] == 39 && is_in_quotes(str, 34, i) == 0)
		{
			i += go_head(str, 39, i + 1);
			if (i >= ft_strlen(str))
				return (0);
		}
		if (str[i] == c)
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
		if (is_expansable(tmp, '$'))
			expand_var(&tmp, envp);
		if (has_quotes(tmp->word))
			expand_quotes(&tmp, has_quotes(tmp->word));
		if (is_expansable(tmp, '*'))
			expand_wildcart(&tmp);
		tmp = tmp->next;
	}
}
