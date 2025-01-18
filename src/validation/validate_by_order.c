/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_by_order.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:23:28 by dasargsy          #+#    #+#             */
/*   Updated: 2025/01/18 23:32:48 by dasargsy         ###   ########.fr       */
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
		
	}	
	return (1);
}

void redirs_case(t_token **tokens)
{
    t_token *tmp;
    t_token *tmp2;

    tmp = *tokens;
    tmp2 = NULL;
    while (tmp)
    {
        if (tmp->type == ONE_REDIR_R_ID || tmp->type == DOUBLE_REDIR_R_ID)
        {
            if (!tmp->last || is_operator(tmp->last))
            {
                tmp2 = new_token(NULL, COMMAND_ID);
                if (tmp->last == NULL)
                {
                    tmp2->next = tmp;
                    tmp->last = tmp2;
                    *tokens = tmp2;
                }
                else
                {
                    tmp2->next = tmp;
                    tmp2->last = tmp->last;
                    tmp->last->next = tmp2;
                    tmp->last = tmp2;
                }
                tmp = tmp->next;
                if (!tmp)
                    return;
            }
        }
        tmp = tmp->next;
    }
}


int	validate_by_order(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		tmp = tmp->next;
	}
	redirs_case(tokens);
	return (1);
}
