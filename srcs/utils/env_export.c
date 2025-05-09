/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:20:01 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/24 12:58:30 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static t_env_lst	*new_env_free_cont(char *name, char *content)
{
	t_env_lst	*new;

	new = ft_calloc(1, sizeof(t_env_lst));
	new->next = NULL;
	new->var_name = name;
	if (content == NULL)
		new->var_cont = NULL;
	else
		new->var_cont = ft_strdup(content);
	return (free(content), ms_get_data()->env_var = env_to_tab(new), new);
}

static t_env_lst	*new_env(char *name, char *content)
{
	t_env_lst	*new;

	new = ft_calloc(1, sizeof(t_env_lst));
	new->next = NULL;
	if (content == NULL)
	{
		new->var_cont = NULL;
		new->var_name = ft_substr(name, 0, ft_strlen(name) - 1);
		free(name);
		name = NULL;
	}
	else
	{
		new->var_cont = ft_strdup(content);
		new->var_name = name;
	}
	return (new);
}

int	env_export(char *name, char *content, t_env_lst **head)
{
	t_env_lst	*tmp;

	if (MS_DEBUG == true && MS_DE_EXPORT == true)
		printf("Debug Exported : "RED"%s"YEL"%s"RES, name, content);
	ft_free_strtab(ms_get_data()->env_var);
	if (ms_get_data()->env_lst == NULL)
		return (ms_get_data()->env_lst = new_env_free_cont(name, content), 1);
	tmp = *head;
	while (tmp->next != NULL && ms_strcmp_e(tmp->var_name, name))
		tmp = tmp->next;
	if (ms_strcmp_e(tmp->var_name, name))
		tmp->next = new_env(name, content);
	else if (!ms_strcmp_e(tmp->var_name, name))
	{
		if (content != NULL)
		{
			(free(tmp->var_name), free(tmp->var_cont));
			tmp->var_name = name;
			tmp->var_cont = ft_strdup(content);
		}
		else
			free(name);
	}
	return (ms_get_data()->env_var = env_to_tab(*head), free(content), 0);
}
