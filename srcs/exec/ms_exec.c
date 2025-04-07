/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnrandom <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:23:43 by johnrandom        #+#    #+#             */
/*   Updated: 2025/04/07 15:55:58 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

int	find_outfile(t_ms_tokken *tokken, t_list *save)
{
	int			outfile;
	t_ms_tokken     *files;

	outfile = -1;
	files = save->content;
	while (files->id == tokken->id)
	{
		if (files->type != CMD && files->type != ARG)
			outfile = outfile_open(outfile, files->type, files->content);
		if (outfile == -2)
			exit(1);
		save = save->next;
		files = save->content;
	}
	return (outfile);
}

int	find_infile(t_ms_tokken *tokken, t_list *save)
{
	int			infile;
	t_ms_tokken	*files;

	infile = -1;
	files = save->content;
	while (files->id == tokken->id)
	{
		if (files->type != CMD && files->type != ARG)
			infile = infile_open(infile, files->type, files->content);
		if (infile == -2)
			exit (1);
		save = save->next;
		files = save->content;
	}
	return (infile);
}

void	cmd_exec(t_ms_tokken *tokken, char **env_var, t_list *save)
{
	char	**cmd;
	int		outfile;
	int		infile;

	infile = find_infile(tokken, save);
	outfile = find_outfile(tokken, save);
	cmd = ft_split(tokken->content, ' ');
	cmd[0] = add_path(cmd[0], env_var);
	if (cmd[0] == NULL)
	{
		ft_free_strtab(cmd);
		exit(1);
	}
	execve(cmd[0], cmd, env_var);
	ft_putstr_fd("Error execve🖕\n", 2);
	(void)infile;
	(void)outfile;
	exit(1);
}

int	ms_exec(t_list *tokkens, t_ms_data *data)
{
	t_list		*temp;
	t_list		*save;
	t_ms_tokken	*tokken;
	t_pids		*pids;

	temp = tokkens;
	save = temp;
	if (files_access(tokkens) == -1)
		return (0);
	pids = new_pids();
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->type == CMD)
		{
			pids->pid = fork();
			if (pids->pid == 0)
				cmd_exec(tokken, data->env_var, save);
			pids = pids->next;
			pids = new_pids();
			save = temp->next;
		}
		temp = temp->next;
	}
	print_pids(pids);
	return (0);
}
