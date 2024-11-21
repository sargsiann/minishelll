/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:04:22 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/21 19:56:31 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_here_doc(t_token **token, t_var *head)
{
	t_token	*tmp;
	char	*line;
	char	*tmp_line;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
		{
			line = readline("> ");
			tmp_line = ft_strdup(tmp->word);
			tmp->word = ft_strjoin(tmp_line, line);
			free(tmp_line);
			free(line);
		}
		tmp = tmp->next;
	}
}
