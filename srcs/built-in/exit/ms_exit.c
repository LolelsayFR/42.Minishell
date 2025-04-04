/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/04 16:46:49 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_exit(char *exit_status, t_ms_data *data)
{
	char	**exit_args;
	int	i;
	int	j;
	int	k;

	if (exit_status == NULL || exit_status[0] == '\0')
		ms_close(EXIT_SUCCESS, data);
	exit_args = ft_split(exit_status, ' ');
	if (ft_tabstr_len(exit_args) == 1)
		ms_close((unsigned char)data->last_return, data);
	i = 0;
	j = 0;
	k = 1;
	while (exit_args[k] != NULL)
	{
		if (ft_str_is_num(exit_args[k]) == 1)
			j++;
		else if (ft_str_is_num(exit_args[k]) == 0)
			i++;
		k++;
	}
	if (i > 1)
		return (EXIT_FAILURE);
	if (j >= 1 && ft_str_is_num(exit_args[1]) == 0)
		return (EXIT_FAILURE);
	if (j >= 1)
		ms_close(2, data);
	ms_close((unsigned char)ft_atol(exit_args[1]), data);
	return (EXIT_FAILURE);
}
