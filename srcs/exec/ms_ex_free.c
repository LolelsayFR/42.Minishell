/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:25:16 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/10 14:33:35 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

void	close_all_pipes(t_ex_data *data)
{
	int	i;

	i = 0;
	while (i < (data->nb_cmd - 1))
	{
		close(data->pipe[i][0]);
		close(data->pipe[i][1]);
		i++;
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
	int	i;

	i = 0;
	while (i < data->nb_cmd - 1)
		free(data->pipe[i++]);
	free(data->pipe);
	free(data->pid);
	free(data);
}

void	exec_end(t_ex_data *data)
{
	close_all_pipes(data);
	wait_all_pids(data);
	free_ex_data(data);
}
