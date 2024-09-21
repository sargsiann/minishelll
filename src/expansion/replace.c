/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 02:36:28 by dasargsy          #+#    #+#             */
/*   Updated: 2024/09/11 22:26:55 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_var(char *name, t_var *vars)
{
	t_var	*tmp;

	tmp = vars;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->key))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

char	*replacer(char *line, int i, int len, t_var *vars)
{
	char	*bef;
	char	*aft;
	char	*value;
	char	*name;

	bef = ft_substr(line, 0, i);
	name = ft_substr(line, i + 1, len);
	value = find_var(name, vars);
	aft = ft_strdup(line + i + len + 1);
	value = ft_gstrjoin(bef, value, 1, 1);
	value = ft_gstrjoin(value, aft, 1, 1);
	free(name);
	free(line);
	return (value);
}
