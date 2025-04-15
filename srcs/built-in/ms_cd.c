/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:20:45 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/15 14:00:59 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_cd_exec(t_ms_data *data, char *pwd, char **path)
{
	if (path[0][0] == '~')
		path[0] = ft_strjoin(get_env(data, "HOME=") + 5, &path[0][1]);
	if (chdir(path[0]) == -1)
	{
		ft_printfd(2, DIR_ERROR, ms_prefix(data), path[0]);
		data->last_return = 1;
		ft_free_strtab(path);
		free(pwd);
		return (1);
	}
	data->last_return = 0;
	ft_free_strtab(path);
	free(pwd);
	return (0);
}

int	ms_cd(t_ms_data *data, char **path)
{
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0);
	data->last_return = 1;
	if (ft_tabstr_len(path) == 0)
	{
		home = get_env(data, "HOME=");
		if (home == NULL)
			return (free(pwd), ft_free_strtab(path), 1);
		free(path[0]);
		path[0] = ft_strdup(home + 5);
	}
	else if (ft_tabstr_len(path) > 1)
		return (free(pwd), ft_free_strtab(path),
			ft_printfd(2, DIR_COUNT, ms_prefix(data)), 1);
	else if (path[0][0] != '~')
	{
		ft_strcat(&pwd, "/");
		ft_strcat(&pwd, path[0]);
	}
	return (ms_cd_exec(data, pwd, path));
}
