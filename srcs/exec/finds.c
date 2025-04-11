/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:07:48 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/11 13:03:46 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

int	*find_previous_pipe(t_ex_data *data, int *pipe)
{
	t_pipe	*temp;

	temp = data->pipes;
	while (temp != NULL && temp->next != NULL)
	{
		if (temp->next->pipe[0] == pipe[0] && temp->next->pipe[1] == pipe[1])
			return (temp->pipe);
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
		if (tokken->type == CMD)
			i++;
		temp = temp->next;
	}
	return (i);
}
