/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnrandom <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:23:43 by johnrandom        #+#    #+#             */
/*   Updated: 2025/04/10 10:19:01 by artgirar         ###   ########.fr       */
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
	while (files->id == tokken->id)
	{
		files = save->content;
		if (files->type != CMD && files->type != ARG)
			infile = infile_open(infile, files->type, files->content);
		if (infile == -2)
			exit (1);
		save = save->next;
	}
	return (infile);
}

void	cmd_exec(t_ms_tokken *tokken, t_list *save, t_ms_data *data)
{
	char	**cmd;
	int		outfile;
	int		infile;

	infile = find_infile(tokken, save);
	outfile = find_outfile(tokken, save);
	cmd = ft_split(tokken->content, ' ');
	cmd[0] = add_path(cmd[0], data->env_var);
	if (cmd[0] == NULL)
	{
		ft_free_strtab(cmd);
		ms_close(2, data);
	}
	execve(cmd[0], cmd, data->env_var);
	(void)infile;
	(void)outfile;
	ms_close(2, data);
}

int	ms_exec(t_ms_data *data, t_list *tokkens)
{
	t_ex_data	*ex_data;
	t_list		*save;
	t_ms_tokken	*tokken;
	int		i;

	i = 0;
	save = tokkens;
	if (files_access(tokkens) == -1)
		return (0);
	ex_data = malloc(sizeof(t_ex_data));
	ex_data->nb_cmd = find_nb_cmd(tokkens);
	ex_data->pid = malloc(ex_data->nb_cmd * sizeof(int));
	while (tokkens != NULL)
	{
		tokken = tokkens->content;
		if (tokken->type == CMD)
		{
			ex_data->pid[i] = fork();
			if (ex_data->pid[i] == 0)
				cmd_exec(tokken, save, data);
			i++;
			save = tokkens->next;
		}
		tokkens = tokkens->next;
	}
	wait_all_pids(ex_data);
	return (data->last_return = 0, 0);
}
