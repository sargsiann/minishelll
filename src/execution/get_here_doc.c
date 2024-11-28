/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:04:22 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/28 20:30:05 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void	hd_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		exit(1); // Exit immediately on SIGINT during here-document
	}
	else if (signo == SIGQUIT)
		; // Ignore SIGQUIT
}

void	get_from_hdoc(char **limiters)
{
	char	*line;
	char	*tmp;
	int		current_limiter;

	current_limiter = 0;
	line = ft_strdup(""); // Initialize line to store accumulated input
	if (!line)
		return; // Handle memory allocation failure
	signal(SIGINT, hd_signal_handler); // Set up signal handler for SIGINT
	signal(SIGQUIT, SIG_IGN);          // Ignore SIGQUIT
	
	while (limiters[current_limiter])
	{
		tmp = readline("> "); // Prompt user for input
		if (!tmp) // Handle CTRL+D (EOF)
		{
			write(1, "Warning: here-document ended unexpectedly (CTRL+D)\n", 52);
			break;
		}

		// Check if input matches the current limiter
		if (ft_strcmp(tmp, limiters[current_limiter]) == 0)
		{
			current_limiter++;
			free(tmp);
			if (!limiters[current_limiter]) // All limiters matched
				break;
			continue;
		}

		// Append input to the accumulated line
		tmp = ft_gstrjoin(tmp, "\n", 1, 0); // Add newline to the input
		line = ft_gstrjoin(line, tmp, 1, 0); // Append to accumulated line
		free(tmp);
	}

	// Output the accumulated input
	if (line && *line)
		write(STDIN_FILENO, line, ft_strlen(line));

	free(line); // Free accumulated input
}

