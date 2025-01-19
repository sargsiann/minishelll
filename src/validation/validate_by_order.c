/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_by_order.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:23:28 by dasargsy          #+#    #+#             */
/*   Updated: 2025/01/19 17:30:43 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

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

int	is_redir(t_token *token)
{
	if (token->type == ONE_REDIR_L_ID || token->type == ONE_REDIR_R_ID
		||token->type == DOUBLE_REDIR_R_ID
		|| token->type == HERE_DOC)
		return (1);
	return (0);
}

void	error_message(char *msg, char *op, int stat)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(op, 2);
	ft_putstr_fd("'\n", 2);
	g_status = stat;
}

static int	check_order(t_token *token)
{
	if (is_operator(token))
	{
		if (token->next == NULL || is_operator(token->next) 
		|| token->last == NULL || is_operator(token->last))
		{
			if (is_redir(token))
			{
				if (token->next && is_operator(token->next))
					return 1;
				if (token->type == ONE_REDIR_L_ID || token->type == HERE_DOC)
					error_message(SYNTAX_ERROR, "newline", 2);
				else
					error_message(SYNTAX_ERROR, "newline", 2);
				return (0);
			}
			if (token->next && is_redir(token->next))
				return 1;
			if (token->type == ONE_REDIR_L_ID || token->type == HERE_DOC)
				error_message(SYNTAX_ERROR, "newline", 2);
			else
				error_message(SYNTAX_ERROR, token->word, 2);
			return (0);
		}
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
	redirs_case(tokens);
	while (tmp)
	{
		if (check_order(tmp) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
