/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnrandom <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:23:43 by johnrandom        #+#    #+#             */
/*   Updated: 2025/04/04 09:46:39 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

int	ms_exec(t_list *tokkens, t_ms_context *context, t_ms_data *data)
{
	t_list	*temp;
	t_files	*files;

	temp = tokkens;
	files = all_open(temp);
	while (temp != NULL)
	{
		if (temp->content->type == CMD)
		{
			pid = fork();
			if (pid == 0)
				cmd_exec(tokken->content, data->env_var, context);
		}
		temp = temp->next;
	}
	return (0);
}
