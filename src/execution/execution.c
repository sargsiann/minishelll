/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:47:54 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/06 17:06:03 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

static int	is_op(void *op)
{
	int	type;

	type = ((t_operator *)op)->type;
	
	return (type == PIPE_ID || type == AND_ID || type == OR_ID);
}

void	execute_right_cmd(t_command *com, int in, int out, char ***envp)
{
	command_execution(com, in, out, envp);
}

void	execute_left_command(t_command *com, int in, int out, char ***envp)
{
	command_execution(com, in, out, envp);
}


void	execute_pipe(t_operator *op, int outfile, char ***envp)
{
	int fd[2];

	pipe(fd);
	if (!is_op(op->left))
	{
		execute_left_command(op->left, -1, fd[1], envp);
		close(fd[1]);
		execute_right_cmd(op->right, fd[0], outfile, envp);
		close(fd[0]);
	}
	else
	{
		execute_pipe(op->left, fd[1], envp);
		close(fd[1]);
		execute_right_cmd(op->right, fd[0], outfile, envp);
		close(fd[0]);
	}
}


// Основная функция для выполнения команд с пайпами
void execution(void *root, char ***envp)
{
    t_operator *op;
    t_command *com;
	pid_t pid;

    op = root;
    com = root;

    if (!is_op(op)) // Если это команда, а не оператор
		command_execution(com, -1, -1, envp);
    else
    {
		if (op->type == PIPE_ID) // Если это оператор пайпа (|)
			execute_pipe(op,-1, envp);
        if (op->type == AND_ID) // Если это оператор И (&&)
        {
            execution(op->left, envp);
            if (g_status == 0)
                execution(op->right, envp);
        }
        else if (op->type == OR_ID) // Если это оператор ИЛИ (||)
        {
            execution(op->left, envp);
            if (g_status != 0)
                execution(op->right, envp);
        }
    }
}
