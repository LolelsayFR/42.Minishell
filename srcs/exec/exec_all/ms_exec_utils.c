/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:25:43 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/24 12:30:37 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	close_cmd_permission(t_ex_data *ex_data)
{
	close_pipe(ex_data);
	if (ex_data->pipe != NULL)
		close(ex_data->pipe[0]);
	exec_close(ex_data, ex_data->cmd, 126, 0);
}

void	close_cmd_or_file(t_ex_data *ex_data)
{
	close_pipe(ex_data);
	if (ex_data->pipe != NULL)
		close(ex_data->pipe[0]);
	if (ex_data->cmd[0] == NULL)
		exec_close(ex_data, ex_data->cmd, 127, 1);
	exec_close(ex_data, ex_data->cmd, 1, 1);
}
