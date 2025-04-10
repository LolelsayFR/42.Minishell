/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:25:16 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/10 15:49:38 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

void	close_all_pipes(t_ex_data *data)
{
	t_pipe	*pipes;

	pipes = data->pipes;
	while (pipes != NULL)
	{
		close(pipes->pipe[0]);
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
	//free(data->pipes);
	free(data->pid);
	free(data);
}

void	exec_end(t_ex_data *data)
{
	//close_all_pipes(data);
	wait_all_pids(data);
	//close_all_pipes(data);
	free_ex_data(data);
}
