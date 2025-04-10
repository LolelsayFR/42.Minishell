/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ex_check_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:29:57 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/10 11:56:33 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

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

void	wait_all_pids(t_ex_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
		waitpid(data->pid[i++], NULL, 0);
}
