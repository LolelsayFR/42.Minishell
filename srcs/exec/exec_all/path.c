/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:08:35 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/15 11:16:40 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

char	*add_path(t_ms_data *data, char *cmd)
{
	int		i;
	char	*joined;
	char	*temp;
	char	**env;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	env = ft_split(get_env(data, "PATH") + 5, ':');
	while (env != NULL && env[i] != NULL)
	{
		temp = ft_strjoin(env[i], "/");
		joined = ft_strjoin(temp, cmd);
		free(temp);
		if (access(joined, F_OK) == 0)
			return (ft_free_strtab(env), joined);
		free(joined);
		i++;
	}
	ft_free_strtab(env);
	return (NULL);
}
