/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comand_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:59:55 by dasargsy          #+#    #+#             */
/*   Updated: 2024/09/15 23:53:13 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_args_size(t_token *t)
{
	int		size;

	size = 0;
	while (t && t->type != COMMAND_ID)
	{
		if (t->type == ARGUMENT_ID)
			size++;
		t = t->next;
	}
	return (size);
}

char	**get_cmd_args(t_token *t)
{
	char	**args;
	t_token	*tmp;
	int		i;

	args = malloc(sizeof(char *) * (get_args_size(t) + 1));
	tmp = t;
	i = 0;
	while (tmp && tmp->type != COMMAND_ID)
	{
		if (tmp->type == ARGUMENT_ID)
		{
			args[i] = ft_strdup(tmp->word);
			i++;
		}
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

char	*get_cmd_infile(t_token *t)
{
	t_token	*tmp;

	tmp = t;
	while (tmp && tmp->type != COMMAND_ID)
	{
		if (tmp->type == INFILE_ID)
			return (ft_strdup(tmp->word));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_cmd_outfile(t_token *t)
{
	t_token	*tmp;

	tmp = t;
	while (tmp && tmp->type != COMMAND_ID)
	{
		if (tmp->type == OUTFILE_ID || tmp->type == APPENDFILE_ID)
			return (ft_strdup(tmp->word));
		tmp = tmp->next;
	}
	return (NULL);
}

int	get_out_type(t_token *t)
{
	t_token	*tmp;

	tmp = t;
	while (tmp && tmp->type != COMMAND_ID)
	{
		if (tmp->type == OUTFILE_ID)
			return (1);
		if (tmp->type == APPENDFILE_ID)
			return (2);
		tmp = tmp->next;
	}
	return (0);
}
