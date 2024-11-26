/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:04:22 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/26 20:06:15 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_from_hdoc(char **limiters)
{
	char	*line;
	int		i;

	i = 0;
	while (limiters[i])
	{
		line = readline("> ");
		if (ft_strcmp(line, limiters[i]) == 0)
		{
			free(line);
			break ;
		}
		add_history(line);
		free(line);
	}
}
