/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/28 11:19:33 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_echo(char *str, int arg)
{
	int	k;

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
		return (ft_printfd(2, NO_SPACE, ms_prefix(ms_get_data()))
			, ms_get_data()->last_return = 1);
	return (ms_get_data()->last_return = 0);
}
