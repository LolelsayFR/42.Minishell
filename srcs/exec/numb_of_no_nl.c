/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numb_of_no_nl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:17:17 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/16 13:30:36 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	is_no_nl(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-' || (str[0] == '-' && str[1] != 'n'))
		return (1);
	while (str[i] != '\0' && str[i] != ' ')
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	numb_of_no_nl(char **tab)
{
	int	i;
	int	numb;

	i = 1;
	numb = 0;
	while (tab[i] != NULL)
	{
		if (is_no_nl(tab[i]) == 1)
			return (numb);
		else
			numb++;
		i++;
	}
	return (numb);
}
