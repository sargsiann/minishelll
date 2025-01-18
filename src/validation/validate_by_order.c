/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_by_order.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:23:28 by dasargsy          #+#    #+#             */
/*   Updated: 2025/01/18 17:12:41 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_operator(t_token *token)
{
	if (token->type != COMMAND_ID
		&& token->type != ARGUMENT_ID && token->type != EXE_ID
		&& token->type != OUTFILE_ID && token->type != INFILE_ID
		&& token->type != APPENDFILE_ID && token->type != DELIMITER_ID
		&& token->type != SEMICOLON_ID)
		return (1);
	return (0);
}

static int	check_order(t_token *token)
{
	if (token->type == SEMICOLON_ID)
	{
		if (token->next == NULL || is_operator(token->next))
			return (0);
	}
	if (token->type == DELIMITER_ID)
	{
		if (token->next == NULL || is_operator(token->next))
			return (0);
	}
	if (token->type == OUTFILE_ID || token->type == INFILE_ID
		|| token->type == APPENDFILE_ID)
	{
		if (token->next == NULL || token->next->type != COMMAND_ID)
			return (0);
	}
	if (token->type == COMMAND_ID)
	{
		if (token->next == NULL || is_operator(token->next))
			return (0);
	}
	return (1);
}

void	redirs_case(t_token **tokens)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *tokens;
	tmp2 = NULL;
	while (tmp)
	{
		if (tmp->type == ONE_REDIR_R_ID  || DOUBLE_REDIR_R_ID)
		{
			if (!tmp->last || is_operator(tmp->last) )
			{
				
			}
		}
	}
}

int	validate_by_order(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (check_order(tmp) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
