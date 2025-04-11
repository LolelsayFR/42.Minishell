/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnrandom <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:23:43 by johnrandom        #+#    #+#             */
/*   Updated: 2025/04/11 09:59:28 by artgirar         ###   ########.fr       */
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
	if (save == NULL && outfile == -1)
		return (1);
	if (outfile == -1)
		return (data->pipes->pipe[1]);
	close(data->pipes->pipe[1]);
	return (outfile);
}

int	find_infile(t_ms_tokken *tokken, t_list *save, t_ex_data *data)
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
		return (data->pipes->pipe[0]);
	close(data->pipes->pipe[0]);
	return (infile);
}

void	cmd_exec(t_ms_tokken *tokken, t_list *save, t_ex_data *ex_data, int *pi)
{
	t_ms_data	*data;
	char		**cmd;
	int			*prev_pi;

	printf("%d\t%d\n", pi[0], pi[1]);
	data = ms_get_data();
	pi[1] = find_outfile(tokken, save, ex_data);
	pi[0] = find_infile(tokken, save, ex_data);
	prev_pi = find_previous_pipe(ex_data, pi);
	cmd = tokken_id_join(data->tokkens, tokken->id);
	cmd[0] = add_path(data, cmd[0]);
	if (cmd[0] == NULL)
		exec_close(ex_data, cmd);
	if (prev_pi != NULL)
	{
			close(pi[0]);
			pi[0] = prev_pi[1];
	}
	printf("%d\t%d\n", pi[0], pi[1]);
	dup2(pi[0], STDIN_FILENO);
	dup2(pi[1], STDOUT_FILENO);
	execve(cmd[0], cmd, data->env_var);
	free_ex_data(ex_data);
	exec_close(ex_data, cmd);
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
				cmd_exec(tokken, save, ex_data, pipes->pipe);
			pipes->next = pipe_init();
			pipes = pipes->next;
		}
		tokkens = tokkens->next;
	}
	return (exec_end(ex_data), data->last_return = 0, 0);
}
