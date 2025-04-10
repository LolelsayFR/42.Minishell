/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnrandom <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:23:43 by johnrandom        #+#    #+#             */
/*   Updated: 2025/04/10 15:10:34 by artgirar         ###   ########.fr       */
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

int	find_outfile(t_ms_tokken *tokken, t_list *save, t_ex_data *data, int i)
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
	if (outfile == -1)
		return (outfile);
	close(data->pipe[i][1]);
	data->pipe[i][1] = outfile;
	return (outfile);
}

int	find_infile(t_ms_tokken *tokken, t_list *save, t_ex_data *data, int i)
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
			exec_close(data, NULL);
		save = save->next;
	}
	if (infile == -1)
		return (infile);
	close(data->pipe[i][0]);
	data->pipe[i][0] = infile;
	return (infile);
}

void	cmd_exec(t_ms_tokken *tokken, t_list *save, t_ex_data *ex_data, int i)
{
	t_ms_data	*data;
	char		**cmd;
	int			outfile;
	int			infile;

	data = ms_get_data();
	outfile = find_outfile(tokken, save, ex_data, i);
	infile = find_infile(tokken, save, ex_data, i);
	cmd = tokken_id_join(data->tokkens, tokken->id);
	cmd[0] = add_path(data, cmd[0]);
	if (cmd[0] == NULL)
		exec_close(ex_data, cmd);
	execve(cmd[0], cmd, data->env_var);
	free_ex_data(ex_data);
	exec_close(ex_data, cmd);
	(void)infile;
	(void)outfile;
}

int	ms_exec(t_ms_data *data, t_list *tokkens)
{
	t_ex_data	*ex_data;
	t_list		*save;
	t_ms_tokken	*tokken;
	int			i;

	i = 0;
	save = tokkens;
	ex_data = exec_init(tokkens);
	while (tokkens != NULL)
	{
		tokken = tokkens->content;
		if (tokken->type == CMD)
		{
			save = first_in_id(data->tokkens, tokken->id);
			if (i != ex_data->nb_cmd - 1)
				if (pipe(ex_data->pipe[i]) == -1)
					break ;
			ex_data->pid[i] = fork();
			if (ex_data->pid[i++] == 0)
				cmd_exec(tokken, save, ex_data, i);
		}
		tokkens = tokkens->next;
	}
	return (exec_end(ex_data), data->last_return = 0, 0);
}
