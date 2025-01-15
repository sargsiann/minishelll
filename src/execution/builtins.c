/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:03:58 by dasargsy          #+#    #+#             */
/*   Updated: 2025/01/15 20:07:42 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// NEED TO WRITE CD 

// FIX UNSET AND EXPORT

extern int	g_status;

void	change_oldpwd(char ***envp, char *oldpwd, char *cur_path)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], "OLDPWD=", 7) == 0)
			(*envp)[i] = ft_strjoin("OLDPWD=", oldpwd);
		if (ft_strncmp((*envp)[i], "PWD=", 4) == 0)
			(*envp)[i] = ft_strjoin("PWD=", cur_path);
		i++;
	}
}

void	pwd()
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
	exit(0);
}

void	cd(char *path, char ***envp)
{
	char	*cur_path;
	char	*old_path;

	old_path = getcwd(NULL, 0);
	if (!path)
		path = ft_strdup(getenv("HOME"));
	if (chdir(path) == -1)
		ft_error(NO_FILE, 1);
	cur_path = getcwd(NULL, 0);
	change_oldpwd(envp, old_path, cur_path);
}

void	my_exit(int	status)
{
	exit(status);
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
	if (!name)
	{
		g_status = 0;
		return (*envp);
	}
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
	g_status = 0;
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
	exit(0);
}

void	echo(char **args)
{
	int	i;

	if (!args[1])
	{
		printf("\n");
		exit(0);
	}
	if (ft_strcmp(args[1],"-n") == 0)
		i = 2;
	else
		i = 1;
	i = 1;
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (ft_strcmp(args[1],"-n") != 0)
		printf("\n");
	exit(0);
}

char	**export(char ***envp, char *value)
{
	int		i;
	char	*new_var;
	char	**new_envp;

	i = 0;
	if (check_var(value) == 0)
	{
		ft_error(" not a valid identifier", 1);
		return (*envp);
	}
	if (!value)
		return (*envp);
	while ((*envp)[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while ((*envp)[i])
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		i++;
	}
	new_var = ft_strdup(value);
	new_envp[i] = new_var;
	new_envp[i + 1] = NULL;
	return (new_envp);
}
