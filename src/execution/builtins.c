/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:03:58 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/28 20:36:13 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// NEED TO WRITE CD 

// FIX UNSET AND EXPORT

void	change_oldpwd(char ***envp, char *oldpwd)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], "OLDPWD=", 7) == 0)
		{
			(*envp)[i] = ft_strjoin("OLDPWD=", oldpwd);
			break ;
		}
		i++;
	}
}

void	cd(char *path, char ***envp)
{
	char	*cur_path;

	cur_path = getcwd(NULL, 0);

	if (chdir(path) == -1)
	{
		ft_error(NO_FILE, NO_FILE_STATUS);
		exit(NO_FILE_STATUS);
	}
	change_oldpwd(envp, cur_path);
}

void	print_history()
{
	HIST_ENTRY	**history;
	int			i;

	i = 0;
	history = history_list();
	if (!history)
		return ;
	while (history[i])
	{
		printf("%d  %s\n", i + 1, history[i]->line);
		i++;
	}
}


char	**unset(char ***envp, char *name)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	while ((*envp)[i])
		i++;
	new_envp = malloc(sizeof(char *) * i);
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i],
			name, ft_strlen(name)) != 0)
		{
			new_envp[j] = ft_strdup((*envp)[i]);
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	return (new_envp);
}

void	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

char	**export(char ***envp, char *name, char *value)
{
	int		i;
	char	*new_var;
	char	**new_envp;

	i = 0;
	if (!value || !name)
		return envp;
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
	new_var = ft_gstrjoin(new_var, value, 1, 1);
	new_envp[i] = new_var;
	new_envp[i + 1] = NULL;
	return (new_envp);
}
