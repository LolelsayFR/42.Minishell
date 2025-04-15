/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:39:01 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/15 11:26:25 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	exec_one_built_in(t_ms_data *data, t_ms_tokken *tokken)
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
	else if (ft_strncmp(tokken->content, "exit\0", 5) == 0)
		do_exit(data, tokken);
	else if (ft_strncmp(tokken->content, "cd\0", 3) == 0)
		do_cd(data, tokken);
}

void	choose_files(int infile, int outfile)
{
	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	if (infile != 0)
		close(infile);
	if (outfile != 1)
		close(outfile);
}

void	exec_cmd(char **cmd, char **env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		execve(cmd[0], cmd, env);
	waitpid(pid, NULL, 0);
}

int	exec_one(t_ms_data *data, t_list *tokkens)
{
	t_ms_tokken	*tokken;
	char		**cmd;
	int			infile;
	int			outfile;

	tokken = tokkens->content;
	infile = find_one_infile(tokkens);
	outfile = find_one_outfile(tokkens);
	if (infile == -1 || outfile == -1)
		return (-1);
	tokkens = find_cmd(tokkens);
	if (tokkens == NULL)
		return (-1);
	cmd = tokken_id_join(data->tokkens, tokken->id);
	cmd[0] = add_path(data, cmd[0]);
	if (cmd[0] == NULL && tokken->type != B_IN)
		return (-1);
	choose_files(infile, outfile);
	if (tokken->type == B_IN)
		exec_one_built_in(data, tokken);
	else
		exec_cmd(cmd, data->env_var);
	return (ft_free_strtab(cmd), data->last_return = 0, 0);
}
