/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:03:54 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/16 15:48:04 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

char	*get_env(t_ms_data *data, char *var)
{
	char	**env;

	env = data->env_var;
	if (env == NULL)
		return (NULL);
	while (*env != NULL && ft_strncmp(*env, var, ft_strlen(var)) != 0)
		env++;
	return (*env);
}
