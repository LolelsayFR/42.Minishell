/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:25:16 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/22 13:33:11 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	wait_all_pids(t_ex_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nb_cmd)
		waitpid(data->pid[i++], &status, 0);
	ms_get_data()->last_return = WEXITSTATUS(status);
}

void	free_ex_data(t_ex_data *data)
{
	if (data->file[0] != 0 && data->file[0] != -1 && data->file[0] != -2)
		close(data->file[0]);
	if (data->file[1] != 1 && data->file[1] != -1 && data->file[1] != -2)
		close(data->file[1]);
	free(data->prev_pipe);
	free(data->pipe);
	free(data->file);
	free(data->pid);
	free(data);
}

void	exec_end(t_ex_data *data)
{
	wait_all_pids(data);
	free_ex_data(data);
	unlink_all();
}

void	exec_close(t_ex_data *ex_data, char **tab, int status, int err)
{
	t_ms_data	*data;

	data = ms_get_data();
	ft_printfd(2, "%s: command not found\n", ex_data->tokken->content);
	free_ex_data(ex_data);
	if (err == 0)
		ft_free_strtab(tab);
	else
		free_tab_err(tab);
	check_standard(4);
	ms_close(status, data);
}
