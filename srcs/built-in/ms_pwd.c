/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/22 08:32:27 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_pwd(t_ms_data *data)
{
	int		i;

	i = printf("%s\n", data->cur_pwd);
	if (i == -1)
		ft_printfd(2, NO_SPACE, ms_prefix(ms_get_data()));
	data->last_return = 0;
	return (0);
}
