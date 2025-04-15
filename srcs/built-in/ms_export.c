/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static void	new_env_export(char *name, char *content, t_env_lst **head)
{
	t_env_lst	*new;
	t_env_lst	*tails;

	ft_strcat(&name, "=");
	new = NULL;
	printf(RED"New\nname = [%s] cont = [%s]"RES, name, content);
	tails = *head;
	printf(GRN"Head\nname = [%s] cont = [%s]"RES, tails->var_name, tails->var_cont);
	while (tails->next->var_name != NULL
		&& ft_strncmp(tails->var_name, name, ft_strlen(tails->var_name)))
		tails = tails->next;
	printf(YEL"Before new\nname = [%s] cont = [%s]"RES, tails->var_name, tails->var_cont);
	if (ft_strncmp(tails->var_name, name, ft_strlen(tails->var_name)))
	{
		new = ft_calloc(1, sizeof(t_env_lst));
		tails->next = new;
		new->var_name = name;
		new->var_cont = content;
	}
	else
		tails->var_cont = content;

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

int	ms_export(t_ms_data *data, char **av)
{
	t_pars_args	a;

	ft_bzero(&a, sizeof(t_pars_args));
	if (ft_tabstr_len(av) <= 0)
		return (print_export(data->env_lst), data->last_return = 1);
	while (av[a.i] != NULL)
	{
		a.len = 0;
		a.count = 0;
		while (av[a.i][a.len] && av[a.i][a.len] != '=')
			a.len++;
		while (av[a.i][a.len + a.count])
			a.count++;
		if (a.count > 0)
			new_env_export(ft_substr(av[a.i], 0, a.len),
				ft_substr(av[a.i], a.len + 1, a.count), &data->env_lst);
		else
			new_env_export(ft_substr(av[a.i], 0, a.len), NULL, &data->env_lst);
		a.i++;
	}
	ft_free_strtab(data->env_var);
	data->env_var = env_to_tab(data->env_lst);
	return (1);
}
