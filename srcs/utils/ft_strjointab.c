/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjointab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:16:44 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/16 08:38:28 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

char	*ft_strjointab(char **tab)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if (tab == NULL)
		return (NULL);
	while (tab[i] != NULL)
	{
		ft_strcat(&str, tab[i]);
		if (tab[i + 1] == NULL)
			return (str);
		ft_strcat(&str, " ");
		i++;
	}
	return (str);
}
