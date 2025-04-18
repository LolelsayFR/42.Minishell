/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/18 16:07:17 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	print_export(t_env_lst *head)
{
	int	count;

	while (head != NULL && head->var_name != NULL)
	{
		count = printf("export %s", head->var_name);
		if (count == -1)
			return (ft_printfd(2, NO_SPACE, ms_prefix(ms_get_data())));
		if (head->var_cont != NULL)
			count = printf("%s", head->var_cont);
		if (count == -1)
			return (ft_printfd(2, NO_SPACE, ms_prefix(ms_get_data())));
		count = printf("\n");
		if (count == -1)
			return (ft_printfd(2, NO_SPACE, ms_prefix(ms_get_data())));
		head = head->next;
	}
	return (0);
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
		env_export(ft_substr(here, 0, a.len + 1),
			ft_substr(av[i], a.len + 1, a.count), &data->env_lst);
		free(here);
		i++;
	}
	ft_free_strtab(data->env_var);
	data->env_var = env_to_tab(data->env_lst);
	return (1);
}
