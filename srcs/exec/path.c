/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:08:35 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/04 13:31:32 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

char	*add_path(char *cmd, char **env)
{
	char	*joined;
	char	*temp;

	if (access(cmd, X_OK) == 0)
		return (cmd);
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
