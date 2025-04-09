/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/09 22:58:29 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static void	ft_envremoveone(t_env_lst **head, t_env_lst *lst)
{
	t_env_lst	*tmp_head;

	if (lst == NULL || *head == NULL)
		return ;
	if (*head == lst)
		*head = (*head)->next;
	tmp_head = *head;
	while (tmp_head->next != lst && tmp_head->next != NULL)
		tmp_head = tmp_head->next;
	if (tmp_head->next != NULL)
		tmp_head->next = tmp_head->next->next;
	else
		return ;
	nufree(lst->var_cont);
	nufree(lst->var_name);
	nufree(lst);
}

int	ms_unset(t_ms_data *data, char *arg)
{
	t_env_lst	*tmp;

	if (arg == NULL)
		return (data->last_return = 0, 0);
	tmp = data->env_lst;
	if (MS_DEBUG == true && MS_DE_UNSET == true)
		ft_putendl_fd(arg, 1);
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->var_name, arg, ft_strlen(tmp->var_name) - 1))
			break ;
		if (MS_DEBUG == true && MS_DE_UNSET == true)
			ft_putendl_fd(tmp->var_name, 1);
		tmp = tmp->next;
	}
	if (tmp != NULL)
		ft_envremoveone(&data->env_lst, tmp);
	data->env_var = env_to_tab(data->env_lst);
	return (data->last_return = 0, 0);
}
