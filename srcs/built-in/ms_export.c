/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/29 14:08:14 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	print_export(t_env_lst *head)
{
	int	count;

	while (head != NULL)
	{
		if (head->var_name == NULL)
		{
			head = head->next;
			continue ;
		}
		count = printf("export %s", head->var_name);
		if (count == -1)
			return (ms_get_data()->last_return = 1,
				ft_printfd(2, NO_SPACE, ms_prefix(ms_get_data())));
		if (head->var_cont != NULL)
			count = printf("%s", head->var_cont);
		if (count == -1)
			return (ms_get_data()->last_return = 1,
				ft_printfd(2, NO_SPACE, ms_prefix(ms_get_data())));
		count = printf("\n");
		if (count == -1)
			return (ms_get_data()->last_return = 1,
				ft_printfd(2, NO_SPACE, ms_prefix(ms_get_data())));
		head = head->next;
	}
	return (ms_get_data()->last_return = 0);
}

static bool	export_checker(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (ms_get_data()->last_return = 1, false);
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (ms_get_data()->last_return = 1, false);
		i++;
	}
	if (i <= 0)
		return (ms_get_data()->last_return = 1, false);
	return (true);
}

static char	*name_convertor(int len, char **av, int i)
{
	if (len == (int)ft_strlen(av[i]))
		return (ft_strjoin(av[i], "="));
	else
		return (ft_strdup(av[i]));
}

static void	ms_export_loop(char **av, t_pars_args *a, int i)
{
	t_ms_data	*data;

	data = ms_get_data();
	while (av[i] != NULL)
	{
		ft_bzero(a, sizeof(t_pars_args));
		while (av[i][a->len] && av[i][a->len] != '=')
			a->len++;
		while (av[i][a->len + a->count])
			a->count++;
		if (export_checker(av[i]) == true && av[i][a->len] != '=')
			env_export(name_convertor(a->len, av, i), NULL, &data->env_lst);
		else if (export_checker(av[i]) == true)
			env_export(ft_substr(av[i], 0, a->len + 1),
				ft_substr(av[i], a->len + 1, a->count), &data->env_lst);
		else
			ft_printfd(2, EXPORT_ERROR, ms_prefix(data), av[i]);
		i++;
	}
}

int	ms_export(t_ms_data *data, char **av)
{
	t_pars_args	a;
	int			i;

	ft_bzero(&a, sizeof(t_pars_args));
	if (ft_tabstr_len(av) <= 0)
		return (print_export(data->env_lst));
	i = 0;
	ms_export_loop(av, &a, i);
	ft_free_strtab(data->env_var);
	data->env_var = env_to_tab(data->env_lst);
	return (1);
}
