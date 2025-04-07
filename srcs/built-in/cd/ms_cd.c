/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:20:45 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/07 11:13:26 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_cd_exec(t_ms_data *data, char *pwd, char **split_path)
{
	if (chdir(pwd) == -1)
	{
		ft_printfd(2, LANG_PREFIX "cd: %s: " DIR_ERROR, split_path[1]);
		data->last_return = 1;
		free(pwd);
		return (1);
	}
	data->last_return = 0;
	free(pwd);
	return (0);
}

int	ms_cd(t_ms_data *data, char *path)
{
	char	*pwd;
	char	**split_path;

	pwd = getcwd(NULL, 0);
	split_path = ft_split(path, ' ');
	if (ft_tabstr_len(split_path) == 1)
		return (data->last_return = 1, 1);
	if (ft_tabstr_len(split_path) > 2)
	{
		data->last_return = 1;
		ft_printfd(2, LANG_PREFIX "cd: " DIR_COUNT);
		return (1);
	}
	if (split_path[1][0] == '/')
	{
		free(pwd);
		pwd = ft_strdup(split_path[1]);
	}
	else
	{
		ft_strcat(&pwd, "/");
		ft_strcat(&pwd, split_path[1]);
	}
	return (ms_cd_exec(data, pwd, split_path));
}
