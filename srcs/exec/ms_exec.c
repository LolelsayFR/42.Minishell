/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnrandom <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:23:43 by johnrandom        #+#    #+#             */
/*   Updated: 2025/04/04 12:27:20 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

int	ms_exec(t_list *tokkens, t_ms_context *context, t_ms_data *data)
{
	t_list		*temp;
	t_files		*files;
	t_ms_tokken	*tokken;
	t_pids		*pids;

	temp = tokkens;
	files = open_all(temp);
	pids = new_pids();
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->type == CMD)
		{
			pids->pid = fork();
			if (pids->pid == 0)
				exit(1);//cmd_exec(tokken, data->env_var, context);
			pids = pids->next;
			pids = new_pids();
		}
		temp = temp->next;
	}
	print_files(files);
	print_pids(pids);
	return (0);
}
