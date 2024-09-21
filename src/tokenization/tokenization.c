/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:43:34 by dasargsy          #+#    #+#             */
/*   Updated: 2024/09/15 17:15:56 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	go_head(char *line, int quote, int index)
{
	int	i;

	i = 0;
	while (line[index] && line[index] != quote)
	{
		i++;
		index++;
	}
	return (i);
}

void	parse_tokens(char *line, char **metas, t_token **head)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = NULL;
	while (line[i])
	{
		if (is_meta(line + i, metas))
		{
			tmp = get_operator(line + i, metas);
			add_token_end(head, tmp);
			if (ft_strlen(tmp->word) == 2)
				i++;
		}
		else if (line[i] && is_word(line, i, metas))
		{
			tmp = new_token(ft_substr(line, i, get_word_size(line, i, metas)),
					ARGUMENT_ID);
			add_token_end(head, tmp);
			i += get_word_size(line, i, metas) - 1;
		}
		i++;
	}
}

t_token	*get_tokens(char *line)
{
	char	**metas;
	t_token	*head;

	head = NULL;
	metas = ft_split(" ( ) | || && > < >> << ", 32, 0);
	parse_tokens(line, metas, &head);
	token_identifier(&head);
	ft_mtx_free(metas);
	return (head);
}
