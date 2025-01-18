/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:38:13 by dasargsy          #+#    #+#             */
/*   Updated: 2025/01/18 14:46:38 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_name(char *name)
{
	int	i;

	i = 0;
	if (!name)
		return (0);
	if (ft_isalpha(name[0]) == 0)
		return (0);
	while (name[i])
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int		check_value(char *value)
{
	int	i;

	i = 0;	
	if (!value)
		return (0);
	while (value[i])
	{
		if (value[i] == '"')
		{
			i += go_head(value, '"',i);
			if (value[i] == '\0')
				return (1);
		}
		i++;
	}
	return (1);
}


int		check_var(char *value)
{
	size_t index;
	char	*name;
	char	*var;

	if (ft_strchr(value, '=') == NULL)
		index = ft_strlen(value);
	else
		index = ft_strchr(value, '=') - value;
	name = ft_substr(value, 0, index);
	var = ft_substr(value, index + 1, ft_strlen(value) - index - 1);
	if (check_name(name) == 0)
		return (0);
	if (check_value(var) == 0)
	{
		return (0);
	}
	return (1);
}

static int	check_exit_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);	
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0 && arg[i] != '-' && arg[i] != '+'
			&& arg[i] != ' ' && arg[i] != 39 && arg[i] != 34)
			return (0);
		i++;
	}
	return (1);
}

int	check_exit_args(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (check_exit_arg(args[i]) == 0 && args[2] == NULL)
			return (1);
		if (i > 1)
			return (2);
		i++;
	}
	return (3);
}