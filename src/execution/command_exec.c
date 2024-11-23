/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:54:53 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/23 19:04:28 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

void	main_exec(t_command *command)
{
	execve(command->word, &command->args[0], NULL);
	ft_error("execve", COMMAND_NOT_FOUND_STATUS);
}

void	get_from_infile(char *infile)
{
	int	fd;

	if (!infile)
		return ;
	if (access(infile, F_OK) == -1)
		ft_error("access", NO_FILE_STATUS);
	fd = open(infile, O_RDONLY);
	if (fd == -1)
		ft_error("open", NO_FILE_STATUS);
	dup2(fd, 0);
	close(fd);
}

void	put_to_outfile(t_outfile *outfiles)
{
	t_outfile	*tmp;
	int			fd;

	tmp = outfiles;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (access(tmp->name, F_OK) == -1)
			ft_error("access", NO_FILE_STATUS);
		if (tmp->type == 1)
			fd = open(tmp->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(tmp->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			ft_error("open", NO_FILE_STATUS);
		if (tmp->next == NULL)
			dup2(fd, STDOUT_FILENO);
		close(fd);
		tmp = tmp->next;
	}
}

void	command_execution(t_command *command, int in, int out)
{
	if (command->here_doc)
		get_from_hdoc(command->here_doc);
	if (command->infile)
		get_from_infile(command->infile);
	if (in != -1 && command->infile == NULL)
		dup2(in, 0);
	if (out != -1 && command->outfiles == NULL)
		dup2(out, 1);
	put_to_outfile(command->outfiles);
	main_exec(command);
}
