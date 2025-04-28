/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/28 13:10:53 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_env(t_ms_data *data)
{
	int	i;
	int	count;

	i = 0;
	while (data->env_var[i] != NULL)
	{
		count = printf("%s\n", data->env_var[i]);
		i++;
	}
	if (count == -1)
	{
		data->last_return = 125;
		ft_printfd(2, NO_SPACE, ms_prefix(ms_get_data()));
	}
	else
		data->last_return = 0;
	return (0);
}
