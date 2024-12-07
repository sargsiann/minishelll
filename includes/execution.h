/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:14:45 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/07 20:27:06 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

void	execution(void *root, char ***envp);
void	get_from_hdoc(char **limiters, int fd);
void	command_execution(t_command *command, int i, int o, char ***envp);
void	main_exec(t_command *command, char **envp);
void	get_from_infile(char *infile);
void	put_to_outfile(t_outfile *outfiles);
char	**unset(char ***envp, char *name);
char	**export(char ***envp, char *value);
void	cd(char *path, char ***envp);
void	print_history(void);
void	env(char **envp);

#endif