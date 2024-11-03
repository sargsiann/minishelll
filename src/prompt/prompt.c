/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 20:41:53 by dasargsy          #+#    #+#             */
/*   Updated: 2024/11/02 18:50:18 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	logic(char *line, char **envp)
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
	// if (validate_by_order(&tokens) == 0)
	// 	return (ft_error(SYNTAX_ERROR, 1));
	expansion(&tokens, envp);
	tree = get_tree(tokens, envp, 0);
	//execution(tree);
	
	// print_tokens(&tokens);
	free_tokens(&tokens);
}

void	prompt(char **envp)
{
	char	*line;

	line = NULL;
	while (1)
	{
		printf("%sMinishell:%s", GREEN, RESET_COLOR);
		line = readline(" ");
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		logic(line, envp);
	}
}
