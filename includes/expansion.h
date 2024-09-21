/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:01:31 by dasargsy          #+#    #+#             */
/*   Updated: 2024/09/14 17:24:13 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "tokenization.h"
# include "../libs/libft/libft.h"
# include <dirent.h>

typedef struct s_var
{
	char			*key;
	char			*value;
	struct s_var	*next;
}	t_var;

typedef struct files
{
	char			*name;
	struct files	*next;
}	t_files;

t_var	*var_new(char *key, char *value);
void	var_add(t_var **head, t_var *var);
t_var	*get_vars(char **envp);
void	expansion(t_token **head, char **envp);
void	free_vars(t_var **head);
void	expand_var(t_token **head, char **envp);
char	*find_var(char *name, t_var *vars);
char	*replacer(char *line, int v_start, int v_len, t_var *vars);
int		is_expansable(t_token *token, char c);
int		is_in_quotes(char *str, char quote, int index);
int		has_quotes(char *str);
int		find_quote_end(char *line, int i, int type);
void	expand_quotes(t_token **token, int type);
void	expand_wildcart(t_token **token);
int		finder(char *pattern, char *file);
t_files	*get_dir_files(t_token *t);
char	*get_pattern(char *str);

#endif