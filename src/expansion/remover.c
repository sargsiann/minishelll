/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remover.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:59:25 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/06 16:31:17 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_quote_start(char *line, int type)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == type)
			return (i);
		i++;
	}
	return (0);
}

int	find_removable(char *line, int s, int e, int type)
{
	int	i;

	i = s + 1;
	while (i < e)
	{
		if (line[i] == type)
			return (i);
		i++;
	}
	return (-1);
}

char	*remover(char *line, int index)
{
	char	*bef;
	char	*aft;
	char	*value;

	bef = ft_substr(line, 0, index);
	aft = ft_strdup(line + index + 1);
	value = ft_gstrjoin(bef, aft, 1, 1);
	free(line);
	return (value);
}

void	expand_quotes(t_token **token, int type)
{
	t_token	*tmp;
	int		end;
	int		start;
	int		remove;

	tmp = *token;
	start = find_quote_start(tmp->word, type);
	end = find_quote_end(tmp->word, start + 1, type);
	remove = start;
	while (remove <= end)
	{
		if (tmp->word[remove] == type)
		{
			tmp->word = remover(tmp->word, remove);
			remove--;
			end--;
		}
		remove++;
	}
	if (tmp->word[0] == 0)
	{
		free(tmp->word);
		tmp->word = NULL;
	}
}
