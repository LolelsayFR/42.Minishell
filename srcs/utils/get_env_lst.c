/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:53:06 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/11 10:21:17 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

t_env_lst	*get_env_lst(t_ms_data *data, char *name)
{
	t_env_lst	*tmp;

	if (name == NULL)
		return (NULL);
	tmp = data->env_lst;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->var_name, name, ft_strlen(tmp->var_name) - 1)
			&& (ft_strlen(name) == ft_strlen(tmp->var_name) - 1))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}
