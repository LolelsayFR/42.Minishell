/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:20:45 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/22 19:03:57 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_cd_exec(t_ms_data *data, char **path, char *temp, char *home)
{
	if (chdir(path[0]) == -1)
	{
		path[0] = temp;
		ft_printfd(2, CD_DIR_ERROR, ms_prefix(data), path[0]);
		free(home);
		return (1);
	}
	env_export(ft_strdup("OLDPWD="), ft_strdup(data->cur_pwd), &data->env_lst);
	free(data->cur_pwd);
	data->cur_pwd = getcwd(NULL, 0);
	env_export(ft_strdup("PWD="), getcwd(NULL, 0), &data->env_lst);
	path[0] = temp;
	free(home);
	return (0);
}

int	ms_cd(t_ms_data *data, char **path)
{
	char	*temp;
	char	*home;

	temp = path[0];
	data->last_return = 1;
	home = get_env(data, "HOME=");
	if (home != NULL)
		home = ft_strdup(home + 5);
	if (ft_tabstr_len(path) == 0)
	{
		if (home == NULL)
			return (ft_printfd(2, CD_NOHOME, ms_prefix(data), 1));
		free(path[0]);
		path[0] = home;
	}
	else if (ft_tabstr_len(path) > 1)
		return (free(home), ft_printfd(2, CD_DIR_COUNT, ms_prefix(data)), 1);
	return (ms_cd_exec(data, path, temp, home));
}
