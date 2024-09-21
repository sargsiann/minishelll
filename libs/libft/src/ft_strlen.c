/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasargsy <dasargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 23:49:32 by anikoyan          #+#    #+#             */
/*   Updated: 2024/08/20 20:01:12 by dasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen(const char *s)
{
	const char	*tmp;

	tmp = s;
	if (!s)
		return (0);
	while (*tmp)
		tmp++;
	return (tmp - s);
}
