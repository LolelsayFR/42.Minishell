/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:07:48 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/18 15:41:06 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	find_outfile(int outfile, int *pipe)
{
	if (outfile != 1)
		return (close(pipe[0]), outfile);
	return (close(pipe[0]), pipe[1]);
}

int	find_infile(int infile, int *pipe)
{
	if (infile != 0)
	{
		if (pipe != NULL)
			close(pipe[0]);
		return (infile);
	}
	if (pipe == NULL)
		return (0);
	return (close(pipe[1]), pipe[0]);
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
