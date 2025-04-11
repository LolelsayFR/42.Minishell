/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnrandom <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:23:43 by johnrandom        #+#    #+#             */
/*   Updated: 2025/04/11 16:35:31 by artgirar         ###   ########.fr       */
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

int	find_outfile(int id, t_list *save, t_ex_data **data, int *pipe)
{
	int			outfile;
	t_ms_tokken	*files;

	outfile = -1;
	files = save->content;
	while (save != NULL && files->id == id)
	{
		files = save->content;
		if (files->type != CMD && files->type != ARG)
			outfile = outfile_open(outfile, files->type, files->content);
		if (outfile == -2)
			exec_close((*data), NULL);
		save = save->next;
	}
	close(pipe[0]);
	if (outfile != -1)
		return (close(pipe[1]), outfile);
	return (pipe[1]);
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
		if (files->type != CMD && files->type != ARG)
			infile = infile_open(infile, files->type, files->content);
		if (infile == -2)
			exec_close((*data), NULL);
		save = save->next;
	}
	if (infile != -1)
	{
		if (pipe != NULL)
			double_close(pipe[0], pipe[1]);
		return (infile);
	}
	if (pipe == NULL)
		return (0);
	return (close(pipe[1]), pipe[0]);
}

void	cmd_exec(int id, t_list *save, t_ex_data **ex_data, int *pi)
{
	t_ms_data	*data;
	char		**cmd;
	int			*prev_pi;
	int			*new_pipe;

	new_pipe = malloc(2 * sizeof(int));
	data = ms_get_data();
	prev_pi = find_previous_pipe((*ex_data), pi);
	new_pipe[1] = find_outfile(id, save, ex_data, pi);
	new_pipe[0] = find_infile(id, save, ex_data, prev_pi);
	cmd = tokken_id_join(data->tokkens, id);
	cmd[0] = add_path(data, cmd[0]);
	if (cmd[0] == NULL)
		exec_close((*ex_data), cmd);
	printf("%d\t%d -> PIPEFILE\n", new_pipe[0], new_pipe[1]);
	dup2(new_pipe[0], STDIN_FILENO);
	dup2(new_pipe[1], STDOUT_FILENO);
	close(new_pipe[0]);
	if (new_pipe[1] != 1)
		close(new_pipe[1]);
	execve(cmd[0], cmd, data->env_var);
	exec_close((*ex_data), cmd);
}

int	ms_exec(t_ms_data *data, t_list *tokkens)
{
	t_ex_data	*ex_data;
	t_list		*save;
	t_pipe		*pipes;
	t_ms_tokken	*tokken;
	int			i;

	i = 0;
	save = tokkens;
	ex_data = exec_init(tokkens);
	pipes = ex_data->pipes;
	while (tokkens != NULL)
	{
		tokken = tokkens->content;
		if (tokken->type == CMD)
		{
			save = first_in_id(data->tokkens, tokken->id);
			if (i < ex_data->nb_cmd - 1)
				if (pipe(pipes->pipe) == -1)
					break ;
			ex_data->pid[i] = fork();
			if (ex_data->pid[i++] == 0)
				cmd_exec(tokken->id, save, &ex_data, pipes->pipe);
			pipes->next = pipe_init();
			pipes = pipes->next;
		}
		tokkens = tokkens->next;
	}
	return (exec_end(ex_data), data->last_return = 0, 0);
}
