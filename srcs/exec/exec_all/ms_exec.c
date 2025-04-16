/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnrandom <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:23:43 by johnrandom        #+#    #+#             */
/*   Updated: 2025/04/16 16:58:57 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	exec_built_in(t_ms_tokken *tokken, t_ms_data *data,
		t_ex_data **ex_data, char **cmd)
{
	if (ft_strncmp(tokken->content, "echo\0", 5) == 0)
		do_echo(data, tokken);
	else if (ft_strncmp(tokken->content, "pwd\0", 4) == 0)
		ms_pwd(data);
	else if (ft_strncmp(tokken->content, "unset\0", 6) == 0)
		do_unset(data, tokken);
	else if (ft_strncmp(tokken->content, "env\0", 4) == 0)
		ms_env(data);
	free_ex_data((*ex_data));
	ft_free_strtab(cmd);
	ms_close(data->last_return, data);
}

int	find_outfile(int id, t_list *save, t_ex_data **data, int *pipe)
{
	int			outfile;
	t_ms_tokken	*files;

	outfile = -1;
	files = save->content;
	while (save != NULL && files->id == id)
	{
		files = save->content;
		if (files->type != CMD && files->type != ARG && files->type != B_IN)
			outfile = outfile_open(outfile, files->type, files->content);
		if (outfile == -2)
			exec_close((*data), NULL, 2, 0);
		save = save->next;
	}
	if (outfile != -1)
		return (close(pipe[1]), outfile);
	return (close(pipe[0]), pipe[1]);
}

int	find_infile(int id, t_list *save, t_ex_data **data, int *pipe)
{
	int			infile;
	t_ms_tokken	*files;

	infile = -1;
	files = save->content;
	while (save != NULL && files->id == id)
	{
		files = save->content;
		if (files->type != CMD && files->type != ARG && files->type != B_IN)
			infile = infile_open(infile, files->type, files->content);
		if (infile == -2)
			exec_close((*data), NULL, 2, 0);
		save = save->next;
	}
	if (infile != -1)
	{
		if (pipe != NULL)
			close(pipe[0]);
		return (infile);
	}
	if (pipe == NULL)
		return (0);
	return (close(pipe[1]), pipe[0]);
}

void	cmd_exec(t_ms_tokken *tokken, t_ex_data **ex_data, int *pi)
{
	t_ms_data	*data;
	char		**cmd;
	int			*prev_pi;

	data = ms_get_data();
	prev_pi = find_previous_pipe((*ex_data), pi);
	(*ex_data)->file[1] = find_outfile(tokken->id,
			(*ex_data)->save, ex_data, pi);
	(*ex_data)->file[0] = find_infile(tokken->id,
			(*ex_data)->save, ex_data, prev_pi);
	cmd = tokken_id_join(data->tokkens, tokken->id);
	cmd[0] = add_path(data, cmd[0]);
	if (cmd[0] == NULL && tokken->type != B_IN)
		exec_close((*ex_data), cmd, 2, 1);
	dup2((*ex_data)->file[0], STDIN_FILENO);
	dup2((*ex_data)->file[1], STDOUT_FILENO);
	if ((*ex_data)->file[0] != 0)
		close((*ex_data)->file[0]);
	if ((*ex_data)->file[1] != 1)
		close((*ex_data)->file[1]);
	if (tokken->type == B_IN)
		exec_built_in(tokken, data, ex_data, cmd);
	else
		execve(cmd[0], cmd, data->env_var);
	exec_close((*ex_data), cmd, 2, 0);
}

int	ms_exec(t_ms_data *data, t_list *tokkens)
{
	t_ex_data	*ex_data;
	t_pipe		*pipes;

	ex_data = exec_init(tokkens);
	ex_data->save = tokkens;
	pipes = ex_data->pipes;
	while (tokkens != NULL)
	{
		ex_data->tokken = tokkens->content;
		if (ex_data->tokken->type == CMD || ex_data->tokken->type == B_IN)
		{
			ex_data->save = first_in_id(data->tokkens, ex_data->tokken->id);
			if (ex_data->i < ex_data->nb_cmd - 1)
				if (pipe(pipes->pipe) == -1)
					break ;
			ex_data->pid[ex_data->i] = fork();
			if (ex_data->pid[ex_data->i++] == 0)
				cmd_exec(ex_data->tokken, &ex_data, pipes->pipe);
			pipes->next = pipe_init();
			pipes = pipes->next;
		}
		tokkens = tokkens->next;
	}
	return (exec_end(ex_data), data->last_return = 0, 0);
}
