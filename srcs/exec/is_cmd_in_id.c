/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd_in_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:48:15 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/22 14:37:06 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	is_cmd_in_id(t_ms_data *data, int id)
{
	t_list		*temp;
	t_ms_tokken	*tokken;

	temp = data->tokkens;
	tokken = temp->content;
	while (temp != NULL && tokken->id != id)
	{
		temp = temp->next;
		tokken = temp->content;
	}
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->id != id)
			break ;
		if (tokken->type == CMD || tokken->type == B_IN)
			return (0);
		temp = temp->next;
	}
	return (1);
}
