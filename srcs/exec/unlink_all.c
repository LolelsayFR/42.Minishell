/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:24:39 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/16 17:27:49 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	unlink_all(void)
{
	t_ms_tokken	*tokken;
	t_list		*temp;
	t_ms_data	*data;

	data = ms_get_data();
	temp = data->tokkens;
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->type == H_D)
			unlink(tokken->content);
		temp = temp->next;
	}
}
