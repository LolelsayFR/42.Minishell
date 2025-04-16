/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/16 15:36:41 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static void	new_env_export(char *name, char *content, t_env_lst **head)
{
	t_env_lst	*new;
	t_env_lst	*tmp;

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
}

static void	print_export(t_env_lst *head)
{
	while (head != NULL && head->var_name != NULL)
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(head->var_name, 1);
		ft_putstr_fd(head->var_cont, 1);
		ft_putstr_fd("\n", 1);
		head = head->next;
	}
}

static char	*name_convertor(int len, char **av, int i)
{
	if (len == (int)ft_strlen(av[i]))
		return (ft_strjoin(av[i], "="));
	else
		return (ft_strdup(av[i]));
}

int	ms_export(t_ms_data *data, char **av)
{
	t_pars_args	a;
	int			i;
	char		*here;

	ft_bzero(&a, sizeof(t_pars_args));
	if (ft_tabstr_len(av) <= 0)
		return (print_export(data->env_lst), data->last_return = 1);
	i = 0;
	while (av[i] != NULL)
	{
		ft_bzero(&a, sizeof(t_pars_args));
		while (av[i][a.len] && av[i][a.len] != '=')
			a.len++;
		here = name_convertor(a.len, av, i);
		while (av[i][a.len + a.count])
			a.count++;
		new_env_export(ft_substr(here, 0, a.len + 1),
			ft_substr(av[i], a.len + 1, a.count), &data->env_lst);
		free(here);
		i++;
	}
	ft_free_strtab(data->env_var);
	data->env_var = env_to_tab(data->env_lst);
	return (1);
}
