/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:53:15 by dasargsy          #+#    #+#             */
/*   Updated: 2024/09/11 22:15:09 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_a(char *after, char *file)
{
	int	end;

	end = 0;
	if (!after)
		return (1);
	end = ft_strlen(file) - ft_strlen(after);
	if (end < 0)
		return (0);
	if (ft_strncmp(after, file + end, ft_strlen(after)) == 0)
		return (1);
	return (0);
}

int	check_b(char *before, char *file)
{
	char	*tmp;
	int		index;

	tmp = NULL;
	index = ft_strchr(before, '*') - before;
	if (!before)
		return (1);
	tmp = ft_substr(before, 0, index);
	if (ft_strncmp(tmp, file, ft_strlen(tmp)) == 0)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int	find_index(char *pattern, char c)
{
	int	i;

	i = ft_strlen(pattern) - 1;
	while (i != -1)
	{
		if (pattern[i] == c)
			return (i);
		i--;
	}
	return (-1);
}

int	finder(char *pattern, char *file)
{
	char	*before;
	char	*after;
	int		index;

	index = find_index(pattern, '*');
	before = ft_substr(pattern, 0, index);
	after = ft_substr(pattern, index + 1, ft_strlen(pattern) - index);
	if (check_b(before, file) && check_a(after, file))
	{
		free(before);
		free(after);
		return (1);
	}
	free(before);
	free(after);
	return (0);
}
