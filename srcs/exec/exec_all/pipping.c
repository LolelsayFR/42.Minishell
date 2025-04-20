/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:18:46 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/20 02:08:28 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	*pipe_savedup(int *pipe)
{
	int	*new_pipe;

	new_pipe = malloc(2 * sizeof(int));
	new_pipe[0] = pipe[0];
	new_pipe[1] = pipe[1];
	return (new_pipe);
}

int	close_pipe(t_ex_data *ex_data)
{
	if (ex_data->nb_cmd - 1 > ex_data->i)
		if (ex_data->pipe != NULL)
			close(ex_data->pipe[1]);
	if (ex_data->prev_pipe != NULL)
		close(ex_data->prev_pipe[0]);
	return (0);
}

int	open_pipe(t_ex_data *ex_data)
{
	if (ex_data->pipe != NULL)
	{
		dup2(ex_data->pipe[0], STDIN_FILENO);
		free(ex_data->prev_pipe);
		ex_data->prev_pipe = pipe_savedup(ex_data->pipe);
	}
	if (ex_data->i < ex_data->nb_cmd - 1)
	{
		free(ex_data->pipe);
		ex_data->pipe = malloc(2 * sizeof(int));
		if (pipe(ex_data->pipe) == -1)
			return (-1);
		dup2(ex_data->pipe[1], STDOUT_FILENO);
	}
	else
		check_standard(2);
	return (0);
}
