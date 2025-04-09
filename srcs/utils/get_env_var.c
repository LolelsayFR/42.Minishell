/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:50:09 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/09 12:30:45 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ft_cmp_env_var(char *var, char *env_var)
{
	int	len;

	len = 0;
	while (env_var[len] != '=')
		len++;
	if (var[len] == '\0')
		if (ft_strncmp(var, env_var, len) == 0)
			return (0);
	return (1);
}

char	*get_env_var(t_ms_data *data, char *var)
{
	int		i;

	i = 0;
	while (data->env_var[i] != NULL)
	{
		if (ft_cmp_env_var(var, data->env_var[i]) == 0)
			return (data->env_var[i]);
		i++;
	}
	return (NULL);
}
