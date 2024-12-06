/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comand_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:59:55 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/06 18:38:24 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_args_size(t_token *t)
{
	int	size;

	size = 1;
	if (t->type == EXE_ID)
		size++;
	else
		t = t->next;
	while (t && t->type != COMMAND_ID && t->type != EXE_ID)
	{
		if (t->type == ARGUMENT_ID && t->word)
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
	args[0] = ft_strdup(t->word);
	tmp = t->next;
	i = 1;
	while (tmp && tmp->type != COMMAND_ID
		&& tmp->type != EXE_ID)
	{
		if (tmp->type == ARGUMENT_ID && tmp->word)
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
	char	*infile;

	tmp = t;
	infile = NULL;
	while (tmp && tmp->type != COMMAND_ID)
	{
		if (tmp->type == INFILE_ID)
			infile = ft_strdup(tmp->word);
		if (tmp->type == HERE_DOC && infile)
		{
			free(infile);
			infile = NULL;
		}
		tmp = tmp->next;
	}
	return (infile);
}

char	**get_here_doc(t_token *t)
{
	t_token	*tmp;
	char	*limter;

	tmp = t;
	limter = ft_strdup("");
	while (tmp && tmp->type != COMMAND_ID)
	{
		if (tmp->type == DELIMITER_ID)
			limter = ft_gstrjoin(limter, tmp->word, 1, 0);
		if (tmp->type == INFILE_ID && limter)
		{
			free(limter);
			limter = NULL;
		}
		limter = ft_gstrjoin(limter, "\n", 1, 0);
		tmp = tmp->next;
	}
	return (ft_split(limter, '\n',1));
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
