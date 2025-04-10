/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:08:35 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/10 11:10:55 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

char	*add_path(t_ms_data *data, char *cmd)
{
	char	*joined;
	char	*temp;
	char	**env;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	env = ft_split(get_env(data, "PATH") + 5, ':');
	while (env != NULL && *env != NULL)
	{
		temp = ft_strjoin(*env, "/");
		joined = ft_strjoin(temp, cmd);
		free(temp);
		if (access(joined, F_OK) == 0)
			return (free(cmd), joined);
		free(joined);
		env++;
	}
	return (NULL);
}
