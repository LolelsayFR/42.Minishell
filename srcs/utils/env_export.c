/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:20:01 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/18 10:47:05 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"


static t_env_lst	*new_env(char *name, char *content)
{
	t_env_lst	*new;

	new = ft_calloc(1, sizeof(t_env_lst));
	new->next = NULL;
	new->var_name = name;
	if (content == NULL)
		new->var_cont = NULL;
	else
		new->var_cont = ft_strdup(content);
	return (ms_get_data()->env_var = env_to_tab(new), new);
}

int	env_export(char *name, char *content, t_env_lst **head)
{
	t_env_lst	*new;
	t_env_lst	*tmp;

	ft_free_strtab(ms_get_data()->env_var);
	if (ms_get_data()->env_lst == NULL)
		return (ms_get_data()->env_lst = new_env(name, content), 1);
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
		new->var_name = name;
		if (content != NULL)
			new->var_cont = ft_strdup(content);
	}
	else if (content != NULL)
		(tmp->var_cont = ft_strdup(content));
	return (ms_get_data()->env_var = env_to_tab(*head), free(content), 0);
}
