/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:18:46 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/18 15:33:45 by artgirar         ###   ########.fr       */
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

int	new_pipe(t_ex_data *ex_data)
{
	int			*pipes;

	pipes = malloc(2 * sizeof(int));
	if (pipe(pipes) == -1)
		return (-1);
	if (ex_data->prev_pipe != NULL)
	{
		dup2(ex_data->prev_pipe[0], STDIN_FILENO);
		close(ex_data->prev_pipe[1]);
		free(ex_data->prev_pipe);
	}
	if (ex_data->nb_cmd - 1 > ex_data->i)
		dup2(pipes[1], STDOUT_FILENO);
	else
		check_standard(2);
	ex_data->prev_pipe = pipe_savedup(pipes);
	free(pipes);
	return (0);
}
