/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 02:22:18 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/04 20:21:25 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	is_simple_var(t_token *token)
{
	char	*str;
	int		i;

	str = token->word;
	i = 0;
	if (str[0] == '$')
	{
		while (str[i++])
		{
			if (ft_isalnum(str[i]) == 0 && str[i] != '_')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	expand_simple_var(t_token *token, t_var *vars)
{
	t_var	*tmp;
	char	*key;
	char	*value;

	tmp = vars;
	key = ft_substr(token->word, 1, ft_strlen(token->word) - 1);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			value = ft_strdup(tmp->value);
			free(token->word);
			token->word = value;
			free(key);
			return ;
		}
		tmp = tmp->next;
	}
	free(token->word);
	token->word = ft_strdup("");
	free(key);
}

int	get_var_len(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isalnum(line[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

void	expand_complex_var(t_token *token, t_var *vars)
{
	t_var	*tmp;
	int		var_len;
	int		i;

	var_len = 0;
	i = 0;
	tmp = vars;
	while (token->word[i])
	{
		if (token->word[i] == '$')
		{
			var_len = get_var_len(token->word + i + 1);
			token->word = replacer(token->word, i, var_len, tmp);
		}
		i++;
	}
}

void	expand_var(t_token **head, char **envp)
{
	t_token	*tmp;
	t_var	*vars;
	t_var	*tmp2;

	vars = get_vars(envp);
	tmp = *head;
	tmp2 = vars;
	if (ft_strcmp(tmp->word, "$?") == 0)
	{
		free(tmp->word);
		tmp->word = ft_itoa(g_status);
		return ;
	}	
	if (is_simple_var(tmp))
		expand_simple_var(tmp, tmp2);
	else
		expand_complex_var(tmp, tmp2);
	tmp = tmp->next;
	free_vars(&vars);
}
