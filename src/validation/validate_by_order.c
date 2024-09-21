/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_by_order.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:23:28 by dasargsy          #+#    #+#             */
/*   Updated: 2024/09/14 19:23:22 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_operator(t_token *token)
{
	if (token->type != COMMAND_ID
		&& token->type != ARGUMENT_ID && token->type != EXE_ID
		&& token->type != OUTFILE_ID && token->type != INFILE_ID
		&& token->type != APPENDFILE_ID)
		return (1);
	return (0);
}

int	validate_by_order(t_token **tokens)
{
	t_token	*tmp;

	if (!tokens)
		return (0);
	tmp = *tokens;
	while (tmp)
	{
		if (is_operator(tmp) && tmp->type != OPEN_BRACE_ID
			&& tmp->type != CLOSE_BRACE_ID)
		{
			if (!tmp->last || !tmp->next || is_operator(tmp->next))
			{
				if (tmp->type == ONE_REDIR_R_ID
					|| tmp->type == DOUBLE_REDIR_R_ID || tmp->type == HERE_DOC)
				{
					if (tmp->next && is_operator(tmp->next) == 0)
						return (1);
				}
				free_tokens(tokens);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
