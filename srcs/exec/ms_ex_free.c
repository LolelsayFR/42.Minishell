/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:25:16 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/11 16:32:22 by artgirar         ###   ########.fr       */
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
	//free(data->pipes);
	free(data->pid);
	free(data);
}

void	exec_end(t_ex_data *data)
{
	write(1, "ici\n", 4);
	close_all_pipes(data);
	wait_all_pids(data);
	write(1, "la\n", 3);
	//close_all_pipes(data);
	free_ex_data(data);
}
