/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/04 15:10:40 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_exit(char *exit_status, t_ms_data *data)
{
	char	**exit_args;

	if (exit_status == NULL || exit_status[0] == '\0')
		ms_close(EXIT_SUCCESS, data);
	exit_args = ft_split(exit_status, ' ');
	if (ft_tabstr_len(exit_args) == 1)
		ms_close((unsigned char)data->last_return, data);
	while (1)
	{
		if (ft_str_is_num(*exit_args) == 1)
			return (EXIT_FAILURE);
		exit_args++;
	}
	// else if ((unsigned char)ft_atoi(exit_status) == 0 && (exit_status[0] != '0'))
	// {
	// 	ft_printfd(2, LANG_EXIT_ERROR, ms_prefix(data), exit_status);	
	// 	return(EXIT_FAILURE);
	// }
	ms_close((unsigned char)ft_atol(exit_status), data);
	return (EXIT_FAILURE);
}
