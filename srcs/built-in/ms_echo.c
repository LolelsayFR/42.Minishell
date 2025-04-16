/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/16 15:15:54 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_echo(char *str, int arg)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (str == NULL)
	{
		if (arg == 0)
			k = write(1, "\n", 1);
	}
	else
	{
		while (str[i] != '\0' && k != -1)
			k = write(1, &str[i++], 1);
		if (arg == 0 && k != -1)
			k = write(1, "\n", 1);
	}
	if (k == -1)
		ft_printfd(2, ECHO_NO_SPACE, ms_prefix());
	return (0);
}
