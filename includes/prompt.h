/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 00:04:31 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/06 16:23:45 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <signal.h>
# include "../libs/libft/libft.h"

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define RESET_COLOR "\x1b[0m"
# define UNCLOSED_Q ""

void	prompt(char **envp);
int		check_for_quotes(char *line, int limiter);
int		check_for_parenthesis(char *line);
void	signal_handler(int signo);
void	logic(char *line, char ***envp);
void	semicolon_case(char *line, char ***envp);

#endif