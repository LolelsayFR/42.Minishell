/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:39:18 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/09 21:17:27 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	print_tab(char **tab)
{
	while (*tab != NULL)
	{
		ft_printf("%s\n", *tab);
		tab++;
	}
}
