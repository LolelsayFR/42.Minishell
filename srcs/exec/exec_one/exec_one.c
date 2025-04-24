/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:39:01 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/24 13:11:32 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	exec_one_built_in(t_ms_data *data, t_one_data *o_data, char **cmd)
{
	ft_free_strtab(cmd);
	if (ft_strncmp(o_data->tokken->content, "echo\0", 5) == 0)
		do_echo(data, o_data->tokken);
	else if (ft_strncmp(o_data->tokken->content, "pwd\0", 4) == 0)
		ms_pwd(data);
	else if (ft_strncmp(o_data->tokken->content, "export\0", 7) == 0)
		do_export(data, o_data->tokken);
	else if (ft_strncmp(o_data->tokken->content, "unset\0", 6) == 0)
		do_unset(data, o_data->tokken);
	else if (ft_strncmp(o_data->tokken->content, "env\0", 4) == 0)
		ms_env(data);
	else if (ft_strncmp(o_data->tokken->content, "exit\0", 5) == 0)
		return (do_exit(data, o_data), (void)1);
	else if (ft_strncmp(o_data->tokken->content, "cd\0", 3) == 0)
		do_cd(data, o_data->tokken);
	free_data(o_data);
}

void	exec_cmd(char **cmd, char **env, t_one_data *o_data)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		check_standard(4);
		execve(cmd[0], cmd, env);
		free_data(o_data);
		if (access(cmd[0], X_OK) == -1)
		{
			ft_free_strtab(cmd);
			ms_close(126, ms_get_data());
		}
		ft_printfd(2, "%s: Command Error\n", cmd[0]);
		ft_free_strtab(cmd);
		ms_close(2, ms_get_data());
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms_get_data()->last_return = WEXITSTATUS(status);
	else if (WTERMSIG(status) == SIGSEGV)
	{
		ms_get_data()->last_return = 139;
		ft_printfd(2, EXEC_SIGSEGV, ms_prefix(ms_get_data()));
	}
	free_data(o_data);
	ft_free_strtab(cmd);
}

int	exec_one(t_ms_data *data, t_list *tokkens)
{
	t_one_data	*o_data;
	char		**cmd;

	o_data = data_init();
	o_data->tokken = tokkens->content;
	check_standard(0);
	if (find_files(o_data, tokkens))
		return (free_data(o_data), data->last_return = 1, -1);
	tokkens = find_cmd(tokkens);
	if (tokkens == NULL)
		return (free_data(o_data), -1);
	cmd = tokken_id_join(data->tokkens, o_data->tokken->id);
	if (o_data->tokken->type != B_IN)
		cmd[0] = add_path(data, cmd[0]);
	if ((cmd[0] == NULL && o_data->tokken->type != B_IN)
		|| o_data->tokken->flag == EMPTY_QUOTE)
		return (free_tab_err(cmd), data->last_return = 127,
			free_data(o_data), -1);
	if (o_data->tokken->type == B_IN)
		exec_one_built_in(data, o_data, cmd);
	else
		exec_cmd(cmd, data->env_var, o_data);
	return (0);
}
