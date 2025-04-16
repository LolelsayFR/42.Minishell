/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:39:01 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/16 13:51:22 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	exec_one_built_in(t_ms_data *data, t_ms_tokken *tokken, char **cmd)
{
	ft_free_strtab(cmd);
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
	else if (ft_strncmp(tokken->content, "exit\0", 5) == 0)
		do_exit(data, tokken);
	else if (ft_strncmp(tokken->content, "cd\0", 3) == 0)
		do_cd(data, tokken);
}

void	exec_cmd(char **cmd, char **env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		execve(cmd[0], cmd, env);
	waitpid(pid, NULL, 0);
	ft_free_strtab(cmd);
}

void	check_standard(int i)
{
	static int	standard[2];

	if (i == 0)
	{
		standard[0] = dup(STDIN_FILENO);
		standard[1] = dup(STDOUT_FILENO);
	}
	else if (i == 1)
	{
		dup2(standard[0], STDIN_FILENO);
		dup2(standard[1], STDOUT_FILENO);
	}
}

int	exec_one(t_ms_data *data, t_list *tokkens)
{
	t_ms_tokken	*tokken;
	char		**cmd;
	int			infile;
	int			outfile;

	tokken = tokkens->content;
	outfile = find_one_outfile(tokkens);
	if (outfile == -1)
		return (-1);
	infile = find_one_infile(tokkens);
	if (infile == -1 && outfile != 1)
		close(outfile);
	if (infile == -1)
		return (-1);
	tokkens = find_cmd(tokkens);
	if (tokkens == NULL)
		return (-1);
	cmd = tokken_id_join(data->tokkens, tokken->id);
	if (tokken->type != B_IN)
		cmd[0] = add_path(data, cmd[0]);
	if (cmd[0] == NULL && tokken->type != B_IN)
		return (free_tab_err(cmd), data->last_return = 1, -1);
	check_standard(0);
	choose_files(infile, outfile);
	if (tokken->type == B_IN)
		exec_one_built_in(data, tokken, cmd);
	else
		exec_cmd(cmd, data->env_var);
	check_standard(1);
	return (0);
}
