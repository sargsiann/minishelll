/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comand_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:59:55 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/21 19:57:46 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_args_size(t_token *t)
{
	int	size;

	size = 0;
	t = t;
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

static void	init(t_outfile **tmp, t_outfile **outfile, t_outfile **head)
{
	*tmp = NULL;
	*outfile = NULL;
	*head = NULL;
}

t_outfile	*get_cmd_outfiles(t_token *command)
{
	t_outfile	*tmp;
	t_outfile	*outfile;
	t_outfile	*head;

	init(&tmp, &outfile, &head);
	while (command && command->type != COMMAND_ID)
	{
		if (command->type == OUTFILE_ID || command->type == APPENDFILE_ID)
		{
			tmp = new_outfile(command);
			if (outfile == NULL)
			{
				outfile = tmp;
				head = outfile;
			}
			else
			{
				outfile->next = tmp;
				outfile = tmp;
			}
		}
		command = command->next;
	}
	return (head);
}
