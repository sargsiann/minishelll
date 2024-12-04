/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 20:41:53 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/04 19:48:40 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

char	**matrix_dup(char **str)
{
	int		i;
	char	**new_str;

	i = 0;
	while (str[i])
		i++;
	new_str = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (str[i])
	{
		new_str[i] = ft_strdup(str[i]);
		i++;
	}
	new_str[i] = NULL;
	return (new_str);
}

void	setup_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTSTP, signal_handler);
}



void	logic(char *line, char ***envp)
{
	t_token	*tokens;
	void	*tree;
	
	if (line[0] == '\0')
		return ;
	if (check_for_parenthesis(line) == 0)
		return (ft_error(UNCLOSING_BRACE, 1));
	if (check_for_quotes(line, 34) == 0)
		return (ft_error(UNCLOSING_DQUOTE, 1));
	if (check_for_quotes(line, 39) == 0)
		return (ft_error(UNCLOSING_QUOTE, 1));
	tokens = get_tokens(line);
	if (validate_by_order(&tokens) == 0)
		return (ft_error(SYNTAX_ERROR, 1));
	expansion(&tokens, *envp);
	tree = get_tree(tokens, *envp, 0);
	// print_tree(tree, 0);
	execution(tree, envp);
	free_tree(tree);
	free_tokens(&tokens);
}

void	prompt(char **env)
{
	char		*line;
	static char	**envp;

	line = NULL;
	envp = matrix_dup(env);
	setup_signals();
	while (1)
	{
		printf("%sMinishell:%s", GREEN, RESET_COLOR);
		line = readline(" ");
		if (!line)
			exit(g_status);
		if (ft_strcmp(line, "history") == 0)
		{
			print_history();
			free(line);
			continue ;
		}
		add_history(line);
		logic(line, &envp);
	}
}
