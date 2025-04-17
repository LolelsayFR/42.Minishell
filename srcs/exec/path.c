/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:08:35 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/17 12:28:22 by artgirar         ###   ########.fr       */
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
	temp = get_env(data, "PATH");
	if (temp == NULL || temp[0] == '\0')
		return (ft_printfd(2, LANG_PREFIX "%s: command not found\n",
				cmd), NULL);
	env = ft_split(temp + 5, ':');
	while (env != NULL && env[i] != NULL)
	{
		temp = ft_strjoin(env[i], "/");
		joined = ft_strjoin(temp, cmd);
		free(temp);
		if (access(joined, F_OK) == 0)
			return (ft_free_strtab(env), free(cmd), joined);
		free(joined);
		i++;
	}
	ft_printfd(2, LANG_PREFIX "%s: command not found\n", cmd);
	return (free(cmd), ft_free_strtab(env), NULL);
}
