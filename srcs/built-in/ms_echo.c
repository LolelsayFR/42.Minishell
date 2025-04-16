/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/16 09:23:21 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_echo(char *str, int arg)
{
	int			i;

	i = 0;
	if (str == NULL)
	{
		if (arg == 0)
			write(1, "\n", 1);
		return (0);
	}
	while (str[i] != '\0')
		write(1, &str[i++], 1);
	if (arg == 0)
		write(1, "\n", 1);
	return (0);
}
