/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:54:17 by dasargsy          #+#    #+#             */
/*   Updated: 2024/12/07 19:08:15 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# include "tokenization.h"

int		validate_by_order(t_token **tokens);
int		validate_var_name(char *name);
int		validate_expanded(t_token **token);
int		check_var(char *value);
int		check_exit_args(char **args);

#endif