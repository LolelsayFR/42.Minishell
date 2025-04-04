/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnrandom <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:23:43 by johnrandom        #+#    #+#             */
/*   Updated: 2025/04/04 10:37:19 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

int	ms_exec(t_list *tokkens, t_ms_context *context, t_ms_data *data)
{
	t_list		*temp;
	t_files		*files;
	t_ms_tokken	*tokken;

	temp = tokkens;
	files = open_all(temp);
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->type == CMD)
		{
			pid = fork();
			if (pid == 0)
				cmd_exec(tokken, data->env_var, context);
		}
		temp = temp->next;
	}
	return (0);
}
