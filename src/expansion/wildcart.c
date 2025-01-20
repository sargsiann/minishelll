/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcart.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:37:00 by dasargsy          #+#    #+#             */
/*   Updated: 2024/09/14 16:01:32 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_files(t_files **head)
{
	t_files	*tmp;

	if (!head || !*head)
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->name);
		free(tmp);
	}
}

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (str[i]);
		i++;
	}
	return (0);
}

int	find_quote_end(char *line, int i, int type)
{
	int	end;

	end = 0;
	while (line[i])
	{
		if (line[i] == type)
			end = i;
		i++;
	}
	return (end);
}

void	expand_wildcart(t_token **token)
{
	t_files	*files;
	t_files	*tmp;
	char	*pattern;
	char	*res;

	files = get_dir_files(*token);
	pattern = get_pattern((*token)->word);
	res = ft_strdup("");
	tmp = files;
	while (tmp)
	{
		if (finder(pattern, tmp->name) && tmp->name[0] != '.')
			res = ft_gstrjoin(res, ft_gstrjoin(tmp->name, " ", 0, 0), 1, 1);
		tmp = tmp->next;
	}
	if (res[0])
	{
		free((*token)->word);
		(*token)->word = ft_strdup(res);
	}
	free(pattern);
	free(res);
	free_files(&files);
}
