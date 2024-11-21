/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:44:45 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/21 19:26:09 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(char *comand, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->word = comand;
	token->type = type;
	token->last = NULL;
	token->next = NULL;
	return (token);
}

void	add_token_end(t_token **token, t_token *new_token)
{
	t_token	*tmp;

	if (!(*token))
	{
		*token = new_token;
		return ;
	}
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
	new_token->last = tmp;
}

int	is_meta_t(t_token *token)
{
	if (token->type == PIPE_ID || token->type == AND_ID
		|| token->type == OR_ID || token->type == ONE_REDIR_R_ID
		|| token->type == ONE_REDIR_L_ID || token->type == DOUBLE_REDIR_R_ID
		|| token->type == HERE_DOC || token->type == OPEN_BRACE_ID
		|| token->type == CLOSE_BRACE_ID)
	{
		return (1);
	}
	return (0);
}

void	free_tokens(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (!tmp)
		return ;
	while (*token)
	{
		tmp = *token;
		free(tmp->word);
		*token = (*token)->next;
		free(tmp);
	}
}

int	go_back(char *line, int quote, int index)
{
	int	i;

	i = 0;
	while (line[index] != quote)
	{
		i++;
		index--;
	}
	return (i);
}
