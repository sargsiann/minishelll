/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:44:53 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/06 22:01:10 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <stdio.h>

int check_for_quotes(char *line)
{
    int i = 0;
    int single_quote = 0; // Tracks single quote state
    int double_quote = 0; // Tracks double quote state

    while (line[i])
    {
        if (line[i] == '\'' && double_quote == 0) // Toggle single quote if not inside double quotes
            single_quote = !single_quote;
        else if (line[i] == '"' && single_quote == 0) // Toggle double quote if not inside single quotes
            double_quote = !double_quote;
        i++;
    }
    // Check if all quotes are properly closed
    if (single_quote || double_quote)
        return (0); // Invalid: Unmatched quotes
    return (1); // Valid: All quotes matched
}


int	check_for_parenthesis(char *line)
{
	int	i;
	int	lft;
	int	rght;

	i = 0;
	lft = 0;
	rght = 0;
	while (line[i])
	{
		if (line[i] == '(')
			lft++;
		if (line[i] == ')')
			rght++;
		i++;
	}
	if (lft == rght)
		return (1);
	else if (lft != rght)
		return (0);
	return (1);
}
