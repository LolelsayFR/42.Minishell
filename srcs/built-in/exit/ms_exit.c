/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/04 10:21:59 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_exit(char *exit_status, t_ms_data *data)
{
	if (exit_status == NULL || exit_status[0] == '\0')
		ms_close(EXIT_SUCCESS, data);
	// else if ((unsigned char)ft_atoi(exit_status) == 0 && (exit_status[0] != '0'))
	// {
	// 	ft_printfd(2, LANG_EXIT_ERROR, ms_prefix(data), exit_status);	
	// 	return(EXIT_FAILURE);
	// }
	else
		ms_close((unsigned char)ft_atol(exit_status), data);
	return (EXIT_SUCCESS);
}

