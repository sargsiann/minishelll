/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_case.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:03:18 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/06 16:23:37 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_in_quote(char *line, int index)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < index)
	{
		if (line[i] == 34)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (0);
	return (1);
}

void	semicolon_case(char *line, char ***envp)
{
	int		i;
	int		j;
	char	*tmp;
	char	**mtx;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == ';' && !is_in_quote(line, i))
		{
			tmp = ft_substr(line, j, i - j);
			mtx = ft_split(tmp, ' ', 0);
			logic(tmp, envp);
			ft_mtx_free(mtx);
			free(tmp);
			j = i + 1;
		}
		i++;
	}
	tmp = ft_substr(line, j, i - j);
	mtx = ft_split(tmp, ' ', 0);
	logic(tmp, envp);
	ft_mtx_free(mtx);
	free(tmp);
}
