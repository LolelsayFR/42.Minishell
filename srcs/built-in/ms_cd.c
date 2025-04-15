/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:20:45 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/15 12:16:07 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_cd_exec(t_ms_data *data, char *pwd, char **split_path, char *path)
{
	if (split_path[0][0] == '~')
		path = ft_strjoin(get_env(data, "HOME=") + 5, &split_path[1][1]);
	if (chdir(path) == -1)
	{
		ft_printfd(2, DIR_ERROR, ms_prefix(data), split_path[1]);
		if (split_path[0][0] == '~')
			free(path);
		data->last_return = 1;
		ft_free_strtab(split_path);
		free(pwd);
		return (1);
	}
	data->last_return = 0;
	if (split_path[0][0] == '~')
		free(path);
	ft_free_strtab(split_path);
	free(pwd);
	return (0);
}

int	ms_cd(t_ms_data *data, char *path)
{
	char	*pwd;
	char	*home;
	char	**split_path;

	pwd = getcwd(NULL, 0);
	split_path = ft_split(path, ' ');
	data->last_return = 1;
	if (ft_tabstr_len(split_path) == 0)
	{
		home = get_env(data, "HOME=");
		if (home == NULL)
			return (free(pwd), ft_free_strtab(split_path), 1);
		path = home + 5;
	}
	else if (ft_tabstr_len(split_path) > 1)
		return (free(pwd), ft_printfd(2, DIR_COUNT, ms_prefix(data)), 1);
	else if (split_path[0][0] == '/')
		path = split_path[1];
	else if (split_path[0][0] != '~')
	{
		ft_strcat(&pwd, "/");
		ft_strcat(&pwd, split_path[0]);
		path = pwd;
	}
	return (ms_cd_exec(data, pwd, split_path, path));
}
