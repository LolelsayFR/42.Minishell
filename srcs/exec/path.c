/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:08:35 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/25 10:54:45 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static char	*error_messages(char *cmd, char **env)
{
	if (access(cmd, F_OK) == -1)
	{
		ft_printfd(2, EXEC_NOFOUND, ms_prefix(ms_get_data()), cmd);
		free(cmd);
		cmd = NULL;
	}
	else
		ft_printfd(2, EXEC_NOPERM, ms_prefix(ms_get_data()), cmd);
	return (ft_free_strtab(env), cmd);
}

char	*add_path(t_ms_data *data, char *cmd)
{
	int		i;
	char	*joined;
	char	*temp;
	char	**env;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	temp = get_env(data, "PATH");
	if (temp == NULL || temp[0] == '\0')
		return (ft_printfd(2, EXEC_NOFOUND, ms_prefix(ms_get_data())
				, cmd), free(cmd), NULL);
	env = ft_split(temp + 5, ':');
	if (ft_strncmp(cmd, "./", 2) == 0)
		return (error_messages(cmd, env));
	while (env != NULL && env[i] != NULL)
	{
		temp = ft_strjoin(env[i++], "/");
		joined = ft_strjoin(temp, cmd);
		free(temp);
		if (access(joined, F_OK) == 0)
			return (ft_free_strtab(env), free(cmd), joined);
		free(joined);
	}
	return (error_messages(cmd, env));
}
