/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/09 08:55:14 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_echo(t_ms_data *data, char *str, int fd)
{
	int			i;

	i = 5;
	if (ft_strncmp(&str[i], "-n ", 3) == 0)
		i += 3;
	while (str[i] != '\0')
		write(fd, &str[i++], 1);
	if (ft_strncmp(str, "-n ", 3) != 0)
		write(1, "\n", 1);
	return (data->last_return = 0, 0);
}
