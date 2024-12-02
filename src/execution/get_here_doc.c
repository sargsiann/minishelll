/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:04:22 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/02 17:31:17 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	g_signal = 0;

void	hd_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("%s%s%s", GREEN, "Minishell: ", RESET_COLOR);
		g_signal = 1;
	}
	else if (signo == SIGQUIT)
		;
}

void	get_from_hdoc(char **limiters)
{
	char	*line;
	char	*tmp;
	int		current_limiter;

	current_limiter = 0;
	line = ft_strdup("");
	if (!line)
		return ;
	signal(SIGINT, hd_signal_handler);
	signal(SIGQUIT, hd_signal_handler);
	while (limiters[current_limiter])
	{
		tmp = readline("> ");
		if (g_signal)
			break ;
		if (!tmp)
		{
			write(1, "Warning: here-doc ended unexpectedly (CTRL+D)\n", 47);
			break ;
		}
		if (ft_strcmp(tmp, limiters[current_limiter]) == 0)
		{
			current_limiter++;
			free(tmp);
			if (!limiters[current_limiter])
				break ;
			continue ;
		}
		tmp = ft_gstrjoin(tmp, "\n", 1, 0);
		if (limiters[current_limiter + 1] == NULL)
			line = ft_gstrjoin(line, tmp, 1, 1);
	}
	if (line && *line)
		write(STDIN_FILENO, line, ft_strlen(line));
	free(line);
}

