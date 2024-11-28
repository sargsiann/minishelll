/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:04:22 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/28 19:19:18 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_from_hdoc(char **limiters)
{
	char	*line;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = ft_strdup("");
	tmp = NULL;
	while (limiters[i])
	{
		tmp = readline("> ");
		if (ft_strcmp(tmp, limiters[j]) == 0)
		{
			j++;
			if (!limiters[j])
			{
				free(tmp);
				write(STDIN_FILENO, line, ft_strlen(line));
				break ;
			}
		}
		if (!limiters[j + 1])
		{
			tmp = ft_gstrjoin(tmp, "\n", 1, 0);
			line = ft_gstrjoin(line, tmp, 1, 0);		
		}
		add_history(tmp);
		free(tmp);
	}
}
