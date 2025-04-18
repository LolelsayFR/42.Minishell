/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ex_check_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:29:57 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/18 13:41:42 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	arg_nb(t_list *tokkens, int id)
{
	int			i;
	t_list		*temp;
	t_ms_tokken	*tokken;

	i = 0;
	temp = tokkens;
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->id != id)
			return (i);
		i++;
		temp = temp->next;
	}
	return (i);
}

t_list	*first_in_id(t_list *tokkens, int id)
{
	t_list		*temp;
	t_ms_tokken	*tokken;

	temp = tokkens;
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->id == id)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_pipe	*pipe_init(void)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	pipe->pipe[0] = 0;
	pipe->pipe[1] = 1;
	pipe->next = NULL;
	return (pipe);
}

t_ex_data	*exec_init(t_list *tokkens)
{
	t_ex_data	*ex_data;

	ex_data = malloc(sizeof(t_ex_data));
	ex_data->nb_cmd = find_nb_cmd(tokkens);
	ex_data->pid = malloc(ex_data->nb_cmd * sizeof(int));
	ex_data->pipes = pipe_init();
	ex_data->prev_pipe = NULL;
	ex_data->file = malloc(2 * sizeof(int));
	ex_data->file[0] = 0;
	ex_data->file[1] = 1;
	ex_data->i = 0;
	return (ex_data);
}
