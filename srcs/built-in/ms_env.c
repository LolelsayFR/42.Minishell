/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/22 18:06:22 by emaillet         ###   ########.fr       */
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
		ft_printfd(2, NO_SPACE, ms_prefix(ms_get_data()));
	data->last_return = 0;
	return (0);
}
