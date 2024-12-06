/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:10:36 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/06 15:42:27 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	meta_identifier(char *line, int len)
{
	if (len == 1)
	{
		if (line[0] == '|')
			return (PIPE_ID);
		if (line[0] == '>')
			return (ONE_REDIR_R_ID);
		if (line[0] == '<')
			return (ONE_REDIR_L_ID);
		if (line[0] == '(')
			return (OPEN_BRACE_ID);
		if (line[0] == ')')
			return (CLOSE_BRACE_ID);
		if (line[0] == ';')
			return (SEMICOLON_ID);
	}
	if (ft_strncmp(line, "||", 2) == 0)
		return (OR_ID);
	if (ft_strncmp(line, "&&", 2) == 0)
		return (AND_ID);
	if (ft_strncmp(line, ">>", 2) == 0)
		return (DOUBLE_REDIR_R_ID);
	if (ft_strncmp(line, "<<", 2) == 0)
		return (HERE_DOC);
	return (-1);
}

int	is_meta(char *line, char **metas)
{
	int	j;

	j = 0;
	while (metas[j])
	{
		if (metas[j][0] == line[0])
		{
			if (line[0] == '&' && metas[j][1] != line[1])
				return (0);
			if (metas[j][1] == line[1])
			{
				return (2);
			}
			return (1);
		}
		j++;
	}
	return (0);
}

static int	is_control(t_token *tmp)
{
	if (tmp->type == PIPE_ID || tmp->type == AND_ID
		|| tmp->type == OR_ID || tmp->type == OPEN_BRACE_ID
		|| tmp->type == CLOSE_BRACE_ID || tmp->type == SEMICOLON_ID)
		return (1);
	return (0);
}

static	void	condition_handling(t_token **tmp)
{
	if ((*tmp)->last && is_control((*tmp)->last))
	{
		if (ft_strncmp((*tmp)->word, "./", 2) == 0)
			(*tmp)->type = EXE_ID;
		else
			(*tmp)->type = COMMAND_ID;
	}
	if ((*tmp)->last->type == ONE_REDIR_R_ID)
		(*tmp)->type = OUTFILE_ID;
	else if ((*tmp)->last->type == ONE_REDIR_L_ID)
		(*tmp)->type = INFILE_ID;
	else if ((*tmp)->last->type == DOUBLE_REDIR_R_ID)
		(*tmp)->type = APPENDFILE_ID;
	else if ((*tmp)->last->type == HERE_DOC)
		(*tmp)->type = DELIMITER_ID;
}

void	token_identifier(t_token **head)
{
	t_token	*tmp;

	if (!*head)
		return ;
	tmp = *head;
	if (tmp->type == ARGUMENT_ID)
	{
		if (ft_strncmp(tmp->word, "./", 2) == 0)
			tmp->type = EXE_ID;
		else
			tmp->type = COMMAND_ID;
	}
	while (tmp)
	{
		if (tmp->type == ARGUMENT_ID)
		{
			condition_handling(&tmp);
		}
		tmp = tmp->next;
	}
}
