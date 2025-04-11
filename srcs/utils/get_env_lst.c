/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:53:06 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/11 09:56:41 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

t_ms_data	*get_env_lst(t_ms_data *data, char *name)
{
	t_env_lst	*tmp;

	if (arg == NULL)
		return (NULL);
	tmp = data->env_lst;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->var_name, arg, ft_strlen(tmp->var_name) - 1)
			&& (ft_strlen(arg) == ft_strlen(tmp->var_name) - 1))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}
