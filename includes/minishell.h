/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:52:21 by dasargsy          #+#    #+#             */
/*   Updated: 2024/09/21 15:15:21 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "prompt.h"
# include "tokenization.h"
# include "validation.h"
# include "expansion.h"
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "gnl.h"
# include "parser.h"
# include "execution.h"

# define UNCLOSING_QUOTE "Unclosed quote"
# define UNCLOSING_DQUOTE "Unclosed double quote"
# define UNCLOSING_BQUOTE "Unclosed back quote"
# define UNCLOSING_BRACKET "Unclosed bracket"
# define UNCLOSING_BRACE "Unclosed brace"
# define UNCLOSING_PARANTHESIS "Unclosed paranthesis"
# define UNKNOWN_COMMAND "command not found"

# define SYNTAX_ERROR "syntax error near unexpected token"
# define VAR_ERROR "not a valid identifier"

# define NO_FILE "No such file or directory"
# define NO_FILE2 "Is a directory"
# define NO_FILE3 "Permission denied"

# define UNCLOSED_STATUS 1
# define SYNTAX_STATUS 2
# define NO_FILE_STATUS 3
# define NO_FILE2_STATUS 4
# define NO_FILE3_STATUS 5
# define VAR_STATUS 6
# define COMMAND_NOT_FOUND_STATUS 7

void	ft_mtx_free(char **mtx);
void	ft_error(char *str, int status);
void	print_vars(t_var *head);

#endif
