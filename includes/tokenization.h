/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:42:43 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/06 15:40:44 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "../libs/libft/libft.h"

# define COMMAND_ID 0
# define PIPE_ID 1
# define ONE_REDIR_R_ID 2
# define ONE_REDIR_L_ID 3
# define DOUBLE_REDIR_R_ID 4
# define HERE_DOC 5
# define AND_ID 6
# define OR_ID 7
# define OPEN_BRACE_ID 8
# define CLOSE_BRACE_ID 9
# define EXE_ID 10
# define INFILE_ID 11 
# define OUTFILE_ID 12
# define APPENDFILE_ID 13 
# define ARGUMENT_ID 15
# define DELIMITER_ID 16
# define SEMICOLON_ID 17

typedef struct s_token
{
	int				type;
	char			*word;
	struct s_token	*next;
	struct s_token	*last;
}	t_token;

t_token	*new_token(char *comand, int type);
void	add_token_end(t_token **token, t_token *new_token);
void	free_tokens(t_token **token);
void	print_tokens(t_token **token);
t_token	*get_tokens(char *line);
int		go_head(char *line, int quote, int index);
int		meta_identifier(char *line, int len);
void	print_matrix(char **mtx);
int		is_meta(char *line, char **metas);
t_token	*get_operator(char *line, char **metas);
int		go_back(char *line, int quote, int index);
int		is_word(char *line, int index, char **metas);
int		get_word_size(char *line, int index, char **metas);
void	token_identifier(t_token **head);
int		is_meta_t(t_token *token);

#endif
