/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:14:45 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/23 18:47:51 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>


void	execution(void *root);
void	get_from_hdoc(char **limiters);
void	command_execution(t_command *command, int i, int o);

#endif