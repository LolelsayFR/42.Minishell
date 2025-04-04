/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnrandom <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:23:43 by johnrandom        #+#    #+#             */
/*   Updated: 2025/04/04 13:38:22 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

void	cmd_exec(t_ms_tokken *tokken, char **env_var, t_files *files)
{
	t_files	*temp;
	char	**cmd;

	temp = files;
	while (temp != NULL && temp->cmd_id != tokken->id)
		temp = temp->next;
	cmd = ft_split(tokken->content, ' ');
	cmd[0] = add_path(cmd[0], env_var);
	if (cmd[0] == NULL)
	{
		ft_free_strtab(cmd);
		exit(1);
	}
	execve(cmd[0], cmd, env_var);
	exit(1);
}

int	ms_exec(t_list *tokkens, t_ms_data *data)
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
				cmd_exec(tokken, data->env_var, files);
			pids = pids->next;
			pids = new_pids();
		}
		temp = temp->next;
	}
	print_files(files);
	print_pids(pids);
	return (0);
}
