/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:54:53 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/24 12:42:40 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

void	main_exec(t_command *command, char **envp)
{
	execve(command->word, &command->args[0], envp);
	ft_error(UNKNOWN_COMMAND, COMMAND_NOT_FOUND_STATUS);
	exit(COMMAND_NOT_FOUND_STATUS);
}

void	get_from_infile(char *infile)
{
	int	fd;

	if (!infile)
		return ;
	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		ft_error(NO_FILE, NO_FILE_STATUS);
		exit(NO_FILE_STATUS);
	}
	if (access(infile, F_OK) == -1)
	{
		ft_error(NO_FILE3, NO_FILE3_STATUS);
		exit(NO_FILE3_STATUS);	
	}
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
		if (tmp->type == APPENDFILE_ID)
			fd = open(tmp->name, O_WRONLY | O_CREAT | O_APPEND, 777);
		else
			fd = open(tmp->name, O_WRONLY | O_CREAT | O_TRUNC, 777);
		if (fd == -1)
			ft_error(NO_FILE, NO_FILE_STATUS);
		if (access(tmp->name, F_OK) == -1)
			ft_error(NO_FILE3, NO_FILE3_STATUS);
		if (tmp->next == NULL)
			dup2(fd, STDOUT_FILENO);
		close(fd);
		tmp = tmp->next;
	}
}

void	command_execution(t_command *command, int in, int out, char **envp)
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
	if (ft_strcmp(command->word, "unset") == 0)
		unset(&envp, command->args[0]);
	else if (ft_strcmp(command->word, "export") == 0)
		export(&envp, command->args[0], command->args[1]);
	else if (ft_strcmp(command->word, "cd") == 0)
		cd(command->args[0], &envp);
	else
		main_exec(command, envp);
}
