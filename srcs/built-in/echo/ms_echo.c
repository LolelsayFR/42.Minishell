/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/03/31 16:09:18 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	echo(char *str, t_bool option)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		write(1, &str[i++], 1);
	if (option == 0)
		write(1, "\n", 1);
}
