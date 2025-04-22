/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/22 16:45:52 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static void	ms_exit_exit(int exit_status, t_ms_data *data, char **tab_free)
{
	ft_free_strtab(tab_free);
	ms_close(exit_status, data);
}

static int	ms_exit_msg(char **exit_args, int i, int j, t_ms_data *data)
{
	if ((i > 1) || (j >= 1 && ft_str_is_num(exit_args[1]) == 0))
	{
		ft_printfd(2, EXIT_COUNT_WRONG, ms_prefix(data));
		data->last_return = 1;
		return (EXIT_FAILURE);
	}
	if ((j >= 1) || (ft_is_ll(exit_args[1]) == 1))
	{
		ft_printfd(2, EXIT_NUM_ERROR, ms_prefix(data), exit_args[1]);
		ms_exit_exit(2, data, exit_args);
	}
	if ((exit_args[1][0] == '-' || exit_args[1][0] == '+')
			&& exit_args[1][1] == '\0')
		ft_printfd(2, EXIT_NUM_ERROR, ms_prefix(data), exit_args[1]);
	ms_exit_exit((unsigned char)ft_atol(exit_args[1]), data, exit_args);
	return (EXIT_FAILURE);
}

int	ms_exit(t_ms_data *data, char **exit_args)
{
	int		i;
	int		j;
	int		k;

	ft_putstr_fd("exit\n", 2);
	if (exit_args == NULL || ft_tabstr_len(exit_args) == 1
		|| exit_args[0][0] == '\0')
		ms_exit_exit((unsigned char)data->last_return, data, exit_args);
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
	return (ms_exit_msg(exit_args, i, j, data));
}
