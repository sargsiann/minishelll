/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:54:11 by dasargsy          #+#    #+#             */
/*   Updated: 2025/01/20 23:18:44 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define PIPE_PR 1
# define AND_PR 2
# define OR_PR 2
# define CM_PR 0

typedef struct s_operator
{
	struct s_operator	*head;
	int					type;
	int					priority;
	void				*left;
	void				*right;
}	t_operator;

typedef struct s_outfile
{
	char				*name;
	int					type;
	struct s_outfile	*next;
}	t_outfile;

typedef struct s_command
{
	struct t_operator	*head;
	int					type;
	char				*word;
	char				**args;
	char				*infile;
	char				**here_doc;
	struct s_outfile	*outfiles;
}	t_command;

void		*get_tree(t_token *tokens, char **envp, int lvl);
void		add_node(t_operator *op, void *node, int direction);
t_operator	*new_operator(t_token *t, int priority);
t_command	*new_command(t_token *t, char **envp);
void		free_tree(void *tree);
int			get_args_size(t_token *t);
char		**get_cmd_args(t_token *t);
char		*get_cmd_infile(t_token *t);
t_outfile	*get_cmd_outfiles(t_token *t);
char		*get_command_path(char **envp, char *command);
t_outfile	*new_outfile(t_token *command);
t_command	*command_case(t_operator **current_op,
				void	**root, t_token *tmp, char **envp);
void		mos_priority_op(void	**root, t_token *tmp,
				t_operator **current_op);

void		operator_case(void	**root, t_token *tmp,
				t_command **current_cmd, t_operator **current_op);
void		mos_priority_op(void	**root, t_token *tmp,
				t_operator **current_op);
char		**get_here_doc(t_token *t);

#endif