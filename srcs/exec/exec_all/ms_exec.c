/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:59:30 by artgirar          #+#    #+#             */
/*   Updated: 2025/05/05 08:59:08 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	exec_built_in(t_ms_tokken *tokken, t_ms_data *data,
		t_ex_data *ex_data, char **cmd)
{
	if (ft_strncmp(tokken->content, "echo\0", 5) == 0)
		do_echo(data, tokken);
	else if (ft_strncmp(tokken->content, "pwd\0", 4) == 0)
		ms_pwd(data);
	else if (ft_strncmp(tokken->content, "export\0", 7) == 0)
		do_export(data, tokken);
	else if (ft_strncmp(tokken->content, "unset\0", 6) == 0)
		do_unset(data, tokken);
	else if (ft_strncmp(tokken->content, "env\0", 4) == 0)
		ms_env(data);
	else if (ft_strncmp(tokken->content, "cd\0", 3) == 0)
		do_cd(data, tokken);
	close_pipe(ex_data);
	close(ex_data->pipe[0]);
	check_standard(4);
	free_ex_data(ex_data);
	ft_free_strtab(cmd);
	ms_close(data->last_return, data);
}

int	finds_files(t_ex_data *ex_data, t_list *tokkens, int id)
{
	t_ms_tokken	*tokken;

	tokken = tokkens->content;
	while (tokkens != NULL)
	{
		tokken = tokkens->content;
		if (tokken->id != id)
			break ;
		if ((tokken->type != CMD && tokken->type != ARG)
			&& tokken->flag == ISEXPAND
			&& ft_countwords(tokken->content, ' ') != 1)
			return (ambigous(tokken->content), -1);
		if (tokken->type == INF || tokken->type == H_D)
			ex_data->file[0] = infile_open(ex_data->file[0],
					tokken->type, tokken->content);
		else if (tokken->type == OUTF_R || tokken->type == OUTF_A)
			ex_data->file[1] = outfile_open(ex_data->file[1],
					tokken->type, tokken->content);
		if (error_filing(ex_data, tokken) == -1)
			return (-1);
		tokkens = tokkens->next;
	}
	return (0);
}

void	cmd_exec(t_ms_tokken *tokken, t_ex_data *ex_data)
{
	t_ms_data	*data;

	data = ms_get_data();
	ex_data->cmd = tokken_id_join(data->tokkens, tokken->id);
	if (tokken->type != B_IN)
		ex_data->cmd[0] = add_path(data, ex_data->cmd[0]);
	ex_data->good_file = finds_files(ex_data, first_in_id(data->tokkens,
				ex_data->tokken->id), ex_data->tokken->id);
	if (ex_data->good_file == -1)
		close_file_permission(ex_data);
	if (ex_data->cmd[0] != NULL && access(ex_data->cmd[0], X_OK) == -1
		&& tokken->type != B_IN)
		close_cmd_permission(ex_data);
	if (ex_data->cmd[0] == NULL || ex_data->good_file == -1)
		close_cmd_none(ex_data);
	if (tokken->type == B_IN)
		exec_built_in(tokken, data, ex_data, ex_data->cmd);
	else
	{
		execve_file_closing(ex_data);
		execve(ex_data->cmd[0], ex_data->cmd, data->env_var);
	}
	ft_printfd(2, "%s: Command Error\n", ex_data->cmd[0]);
	exec_close(ex_data, ex_data->cmd, 2, 0);
}

static inline void	exec_launch(t_ms_data *data, t_ex_data *ex_data)
{
	if (is_cmd_in_id(data, ex_data->tokken->id) == 0)
	{
		ex_data->pid[ex_data->id] = fork();
		if (ex_data->pid[ex_data->id++] == 0)
			cmd_exec(ex_data->tokken, ex_data);
	}
	else
		are_files_good(data, ex_data);
	close_pipe(ex_data);
	ex_data->i++;
}

int	ms_exec(t_ms_data *data, t_list *tokkens)
{
	t_ex_data	*ex_data;

	if (find_nb_pipe(tokkens) == 0)
		return (exec_one(data, tokkens));
	ex_data = exec_init(tokkens);
	while (tokkens != NULL)
	{
		ex_data->tokken = tokkens->content;
		if (ex_data->tokken->id == ex_data->i)
		{
			if (open_pipe(ex_data) == -1)
				break ;
			exec_launch(data, ex_data);
		}
		tokkens = tokkens->next;
	}
	return (check_standard(3), exec_end(ex_data), 0);
}
