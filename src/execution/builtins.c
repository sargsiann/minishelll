/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:03:58 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/24 12:46:47 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// NEED TO WRITE CD 

// FIX UNSET AND EXPORT

void	change_oldpwd(char ***envp)
{
	
}

void	cd(char *path, char ***envp)
{
	if (chdir(path) == -1)
	{
		ft_error(NO_FILE, NO_FILE_STATUS);
		exit(NO_FILE_STATUS);
	}
	*envp = ft_split(getenv(path), '\n', 0);
}


void	unset(char ***envp, char *name)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	while (*envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * i);
	i = 0;
	while (*envp[i])
	{
		if (ft_strncmp(*envp[i], name, ft_strlen(name)) != 0)
		{
			new_envp[j] = ft_strdup(*envp[i]);
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	*envp = new_envp;
}

void	export(char ***envp, char *name, char *value)
{
	int		i;
	char	*new_var;
	char	**new_envp;

	i = 0;
	while (*envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (*envp[i])
	{
		new_envp[i] = ft_strdup(*envp[i]);
		i++;
	}
	new_var = ft_strjoin(name, "=");
	new_var = ft_strjoin(new_var, value);
	new_envp[i] = new_var;
	new_envp[i + 1] = NULL;
	*envp = new_envp;
}
