/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:07:48 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/17 13:18:49 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	find_outfile(int *pipe)
{
	int	outfile;

	outfile = -1;
	if (outfile != -1)
		return (close(pipe[1]), outfile);
	return (close(pipe[0]), pipe[1]);
}

int	find_infile(int *pipe)
{
	int	infile;

	infile = -1;
	if (infile != -1)
	{
		if (pipe != NULL)
			close(pipe[0]);
		return (infile);
	}
	if (pipe == NULL)
		return (0);
	return (close(pipe[1]), pipe[0]);
}

int	*find_previous_pipe(t_ex_data *data, int *pipe)
{
	t_pipe	*temp;

	temp = data->pipes;
	while (temp != NULL && temp->next != NULL)
	{
		if (temp->next->pipe[0] == pipe[0] && temp->next->pipe[1] == pipe[1])
			return (temp->pipe);
		double_close(temp->pipe[0], temp->pipe[1]);
		temp = temp->next;
	}
	return (NULL);
}

int	find_nb_cmd(t_list *tokkens)
{
	int			i;
	t_list		*temp;
	t_ms_tokken	*tokken;

	i = 0;
	temp = tokkens;
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->type == CMD || tokken->type == B_IN)
			i++;
		temp = temp->next;
	}
	return (i);
}
