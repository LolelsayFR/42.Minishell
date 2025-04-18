/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:25:16 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/18 10:35:59 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	close_all_pipes(t_ex_data *data)
{
	t_pipe	*pipes;

	pipes = data->pipes;
	while (pipes != NULL)
	{
		if (pipes->pipe[0] != 0 && pipes->pipe[0] != -1)
			close(pipes->pipe[0]);
		if (pipes->pipe[1] != 1 && pipes->pipe[1] != -1)
			close(pipes->pipe[1]);
		pipes = pipes->next;
	}
}

void	wait_all_pids(t_ex_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
		waitpid(data->pid[i++], NULL, 0);
}

void	free_ex_data(t_ex_data *data)
{
	t_pipe	*pipes;
	t_pipe	*temp;

	pipes = data->pipes;
	while (pipes != NULL)
	{
		temp = pipes->next;
		free(pipes);
		pipes = temp;
	}
	if (data->file[0] != 0)
		close(data->file[0]);
	if (data->file[1] != 1)
		close(data->file[1]);
	free(data->file);
	free(data->pid);
	free(data);
}

void	exec_end(t_ex_data *data)
{
	close_all_pipes(data);
	wait_all_pids(data);
	//close_all_pipes(data);
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
	ms_close(status, data);
}
