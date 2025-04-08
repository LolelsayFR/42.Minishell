/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_home.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:03:54 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/07 18:27:50 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

char	*get_env(t_ms_data *data, char *var)
{
	char	**env;

	env = data->env_var;
	while (*env != NULL && ft_strncmp(*env, var, ft_strlen(var)) != 0)
		env++;
	return (*env);
}
