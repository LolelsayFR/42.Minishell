/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:25:43 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/24 13:30:05 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	execve_file_closing(t_ex_data *ex_data)
{
	if (ex_data->pipe != NULL)
		double_close(ex_data->pipe[0], ex_data->pipe[1]);
	close_pipe(ex_data);
	check_standard(4);
}

void	close_file_permission(t_ex_data *ex_data)
{
	close_pipe(ex_data);
	if (ex_data->pipe != NULL)
		close(ex_data->pipe[0]);
	exec_close(ex_data, ex_data->cmd, 1, 1);
}

void	close_cmd_permission(t_ex_data *ex_data)
{
	close_pipe(ex_data);
	if (ex_data->pipe != NULL)
		close(ex_data->pipe[0]);
	exec_close(ex_data, ex_data->cmd, 126, 0);
}

void	close_cmd_none(t_ex_data *ex_data)
{
	close_pipe(ex_data);
	if (ex_data->pipe != NULL)
		close(ex_data->pipe[0]);
	exec_close(ex_data, ex_data->cmd, 127, 1);
}

void	close_execve_one(t_one_data *o_data, char **cmd)
{
	free_data(o_data);
	if (access(cmd[0], X_OK) == -1)
	{
		ft_free_strtab(cmd);
		ms_close(126, ms_get_data());
	}
	write(1, "ici\n", 4);
	ft_printfd(2, "%s: Command Error\n", cmd[0]);
	ft_free_strtab(cmd);
	ms_close(2, ms_get_data());
}
