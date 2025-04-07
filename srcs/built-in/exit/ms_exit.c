/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/07 10:11:44 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	ms_exit_returns(char **exit_args, int i, int j, t_ms_data *data)
{
	if (i > 1)
	{
		ft_printfd(2, LANG_PREFIX "exit:" COUNT_WRONG);
		return (EXIT_FAILURE);
	}
	if (j >= 1 && ft_str_is_num(exit_args[1]) == 0)
	{
		ft_printfd(2, LANG_PREFIX "exit:" COUNT_WRONG);
		return (EXIT_FAILURE);
	}
	if (j >= 1)
	{
		ft_printfd(2, LANG_PREFIX "exit: %s : " NUMERIC_ERROR, exit_args[1]);
		ms_close(2, data);
	}
	if (ft_is_ll(exit_args[1]) == 1)
	{
		ft_printfd(2, LANG_PREFIX "exit: %s : " NUMERIC_ERROR, exit_args[1]);
		ms_close(2, data);
	}
	write(1, "ici\n", 4);
	ms_close((unsigned char)ft_atol(exit_args[1]), data);
	return (EXIT_FAILURE);
}

int	ms_exit(char *exit_status, t_ms_data *data)
{
	char	**exit_args;
	int		i;
	int		j;
	int		k;

	ft_putstr_fd("exit\n", 2);
	exit_args = ft_split_lst(exit_status, ' ');
	if (exit_status == NULL || ft_tabstr_len(exit_args) == 1
		|| exit_status[0] == '\0')
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
	return (ms_exit_returns(exit_args, i, j, data));
}
