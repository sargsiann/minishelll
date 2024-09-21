/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:23:58 by dasargsy          #+#    #+#             */
/*   Updated: 2024/09/14 16:52:23 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*get_operator(char *line, char **metas)
{
	int		i;

	i = 0;
	if (line[i] == '(')
		return (new_token(ft_strdup("("), 8));
	if (line[i] == ')')
		return (new_token(ft_strdup(")"), 9));
	while (metas[i])
	{
		if (line[0] == metas[i][0]
		&& metas[i][1] && line[0] == line[1])
		{
			return (new_token(ft_strdup(metas[i]), meta_identifier(line, 2)));
		}
		if (line[0] == metas[i][0]
			&& !metas[i][1] && line[0] != line[1])
		{
			return (new_token(ft_strdup(metas[i]), meta_identifier(line, 1)));
		}
		i++;
	}
	return (NULL);
}
