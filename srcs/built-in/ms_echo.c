/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/18 11:00:13 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_echo(char *str, int arg)
{
	//int	i;
	int	k;

	//i = 0;
	k = 0;
	if (str == NULL)
	{
		if (arg == 0)
			k = printf("\n");
	}
	else
	{
		k = printf("%s", str);
		if (arg == 0 && k != -1)
			k = printf("\n");
	}
	if (k == -1)
		ft_printfd(2, ECHO_NO_SPACE, ms_prefix(ms_get_data()));
	return (0);
}
