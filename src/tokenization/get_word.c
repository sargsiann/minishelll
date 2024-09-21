/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:38:47 by dasargsy          #+#    #+#             */
/*   Updated: 2024/09/03 19:12:28 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_word(char *line, int index, char **metas)
{
	if (is_meta(line + index, metas))
		return (0);
	if (ft_isspace(line[index]))
		return (0);
	if (index == 0)
		return (1);
	if (index != 0 && (ft_isspace(line[index - 1])
			|| is_meta(line + index - 1, metas)))
		return (1);
	return (0);
}

int	get_word_size(char *line, int index, char **metas)
{
	int	i;

	i = 0;
	if (line[index] && (line[index] == 34 || line[index] == 39))
	{
		i++;
		while (line[index + i] && line[index + i] != line[index])
			i++;
	}
	while (line[index + i] && !ft_isspace(line[index + i]))
	{
		if (is_meta(line + index + i, metas))
			break ;
		i++;
	}
	return (i);
}
