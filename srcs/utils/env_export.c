/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:20:01 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/17 12:21:55 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	env_export(char *name, char *content, t_env_lst **head)
{
	t_env_lst       *new;
	t_env_lst       *tmp;

	if (ft_strlen(content) == 0)
		(free(content), content = NULL);
	new = NULL;
	tmp = *head;
	while (tmp->next != NULL && ft_strcmp(tmp->var_name, name))
		tmp = tmp->next;
	if (ft_strcmp(tmp->var_name, name))
	{
		new = ft_calloc(1, sizeof(t_env_lst));
		tmp->next = new;
		new->next = NULL;
		new->var_name = name;
		if (content == NULL)
			new->var_cont = NULL;
		else
			new->var_cont = ft_strdup(content);
	}
	else if (content != NULL)
		(tmp->var_cont = ft_strdup(content));
	free(content);
}
