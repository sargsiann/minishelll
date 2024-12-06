/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_case.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:03:18 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/06 22:09:32 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_symbol_in_quotes(char *line, char symbol)
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

        if (line[i] == symbol) // Found the symbol
        {
            if (single_quote || double_quote) // Inside a quoted section
                return 1;
            else
                return 0; // Outside quotes
        }
        i++;
    }

    return -1; // Symbol not found in the string
}

void	semicolon_case(char *line, char ***envp)
{
	int		i;
	int		j;
	char	*tmp;
	char	**mtx;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == ';' && is_symbol_in_quotes(line, ';') == 0)
		{
			tmp = ft_substr(line, j, i - j);
			mtx = ft_split(tmp, ' ', 0);
			logic(tmp, envp);
			ft_mtx_free(mtx);
			free(tmp);
			j = i + 1;
		}
		i++;
	}
	tmp = ft_substr(line, j, i - j);
	mtx = ft_split(tmp, ' ', 0);
	logic(tmp, envp);
	ft_mtx_free(mtx);
	free(tmp);
}
