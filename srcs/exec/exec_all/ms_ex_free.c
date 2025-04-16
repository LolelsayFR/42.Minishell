/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:25:16 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/16 12:18:17 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	close_all_pipes(t_ex_data *data)
{
	t_pipe	*pipes;

	pipes = data->pipes;
	while (pipes != NULL)
	{
		if (pipes->pipe[0] != 0 && pipes->pipe[0] != 1)
			close(pipes->pipe[0]);
		if (pipes->pipe[1] != 0 && pipes->pipe[1] != 1)
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
	free(data->pid);
	free(data);
}

void	exec_end(t_ex_data *data)
{
	close_all_pipes(data);
	wait_all_pids(data);
	free_ex_data(data);
}

void	exec_close(t_ex_data *ex_data, char **tab, int status, int err, int *pi)
{
	t_ms_data	*data;

	data = ms_get_data();
	ft_putstr_fd("Command Error\n", 2);
	free_ex_data(ex_data);
	if (err == 0)
		ft_free_strtab(tab);
	else
		free_tab_err(tab);
	if (pi != NULL)
	{
		if (pi[0] != 0)
			close(pi[0]);
		if (pi[1] != 1)
			close(pi[1]);
	}
	free(pi);
	ms_close(status, data);
}
