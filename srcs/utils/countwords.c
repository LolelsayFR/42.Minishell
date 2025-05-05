/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countwords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 08:43:50 by artgirar          #+#    #+#             */
/*   Updated: 2025/05/05 08:47:42 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ft_countwords(char const *s, char c)
{
	int	nb;
	int	prev;

	nb = 0;
	prev = 0;
	if (!s)
		return (0);
	while (*s != '\0')
	{
		if (prev == 2 && *s == c && prev != 0)
		{
			prev = 1;
			nb++;
		}
		if (*s != c)
			prev = 2;
		s++;
		if (prev == 2 && *s == '\0')
			nb++;
	}
	return (nb);
}
