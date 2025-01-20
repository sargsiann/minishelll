/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcart_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:41:41 by dasargsy          #+#    #+#             */
/*   Updated: 2025/01/20 16:11:52 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_dir(char *str)
{
	int	len;

	len = ft_strchr(str, '*') - str;
	while (len > 0 && str[len] != '/')
		len--;
	if (len == 0)
		return (ft_strdup("./"));
	return (ft_substr(str, 0, len));
}

char	*get_pattern(char *str)
{
	int	len;

	len = ft_strchr(str, '*') - str;
	while (len && str[len] != '/')
		len--;
	return (ft_substr(str, len, ft_strlen(str) - len));
}

void	add_file(t_files **head, t_files *file)
{
	t_files	*tmp;

	if (*head == NULL)
	{
		*head = file;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = file;
}

t_files	*new_file(char *name)
{
	t_files	*file;

	file = malloc(sizeof(t_files));
	if (file == NULL)
		return (NULL);
	file->name = ft_strdup(name);
	file->next = NULL;
	return (file);
}

t_files	*get_dir_files(t_token *t)
{
	struct dirent	*entry;
	DIR				*dp;
	char			*dir;
	t_files			*files;

	dir = get_dir(t->word);
	dp = opendir(dir);
	free(dir);
	if (dp == NULL)
		ft_error(NO_FILE, NO_FILE_STATUS);
	files = NULL;
	while (1)
	{
		entry = readdir(dp);
		if (entry == NULL)
			break ;
		add_file(&files, new_file(entry->d_name));
	}
	closedir(dp);
	return (files);
}
