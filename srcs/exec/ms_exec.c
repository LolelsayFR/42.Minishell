/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnrandom <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:23:43 by johnrandom        #+#    #+#             */
/*   Updated: 2025/04/10 13:52:09 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

void	exec_close(t_ex_data *ex_data, char **tab)
{
	t_ms_data	*data;

	data = ms_get_data();
	ft_putstr_fd("Command Error\n", 2);
	free_ex_data(ex_data);
	ft_free_strtab(tab);
	ms_close(2, data);
}

int	find_outfile(t_ms_tokken *tokken, t_list *save, t_ex_data *data)
{
	int			outfile;
	t_ms_tokken	*files;

	outfile = -1;
	files = save->content;
	while (save != NULL && files->id == tokken->id)
	{
		files = save->content;
		if (files->type != CMD && files->type != ARG)
			outfile = outfile_open(outfile, files->type, files->content);
		if (outfile == -2)
			exec_close(data, NULL);
		save = save->next;
	}
	return (outfile);
}

int	find_infile(t_ms_tokken *tokken, t_list *save, t_ex_data *data, int o)
{
	int			infile;
	t_ms_tokken	*files;

	infile = -1;
	files = save->content;
	while (save != NULL && files->id == tokken->id)
	{
		files = save->content;
		if (files->type != CMD && files->type != ARG)
			infile = infile_open(infile, files->type, files->content);
		if (infile == -2)
		{
			close(o);
			exec_close(data, NULL);
		}
		save = save->next;
	}
	return (infile);
}

void	cmd_exec(t_ms_tokken *tokken, t_list *save, t_ex_data *ex_data)
{
	t_ms_data	*data;
	char		**cmd;
	int			outfile;
	int			infile;

	data = ms_get_data();
	outfile = find_outfile(tokken, save, ex_data);
	infile = find_infile(tokken, save, ex_data, outfile);
	cmd = tokken_id_join(data->tokkens, tokken->id);
	cmd[0] = add_path(data, cmd[0]);
	if (cmd[0] == NULL)
		exec_close(ex_data, cmd);
	execve(cmd[0], cmd, data->env_var);
	(void)infile;
	free_ex_data(ex_data);
	exec_close(ex_data, cmd);
}

int	ms_exec(t_ms_data *data, t_list *tokkens)
{
	t_ex_data	*ex_data;
	t_list		*save;
	t_ms_tokken	*tokken;
	int			i;

	i = 0;
	save = tokkens;
	ex_data = malloc(sizeof(t_ex_data));
	ex_data->nb_cmd = find_nb_cmd(tokkens);
	ex_data->pid = malloc(ex_data->nb_cmd * sizeof(int));
	while (tokkens != NULL)
	{
		tokken = tokkens->content;
		if (tokken->type == CMD)
		{
			save = first_in_id(data->tokkens, tokken->id);
			ex_data->pid[i] = fork();
			if (ex_data->pid[i++] == 0)
				cmd_exec(tokken, save, ex_data);
		}
		tokkens = tokkens->next;
	}
	wait_all_pids(ex_data);
	free_ex_data(ex_data);
	return (data->last_return = 0, 0);
}
