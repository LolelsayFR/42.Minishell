/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:53:41 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/29 14:50:21 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	do_echo(t_ms_data *data, t_ms_tokken *tokken)
{
	int		no_nl;
	char	*str;
	char	**tab;

	tab = tokken_id_join(data->tokkens, tokken->id);
	no_nl = numb_of_no_nl(tab);
	if (no_nl > 0)
	{
		str = ft_strjointab(&tab[1 + no_nl]);
		data->last_return = ms_echo(str, 1);
	}
	else
	{
		str = ft_strjointab(&tab[1]);
		data->last_return = ms_echo(str, 0);
	}
	free(str);
	ft_free_strtab(tab);
}

void	do_unset(t_ms_data *data, t_ms_tokken *tokken)
{
	char	**tab;

	tab = tokken_id_join(data->tokkens, tokken->id);
	ms_unset(data, &tab[1]);
	ft_free_strtab(tab);
}

void	do_export(t_ms_data *data, t_ms_tokken *tokken)
{
	char	**tab;

	tab = tokken_id_join(data->tokkens, tokken->id);
	ms_export(data, &tab[1]);
	ft_free_strtab(tab);
}

void	do_cd(t_ms_data *data, t_ms_tokken *tokken)
{
	char	**tab;

	tab = tokken_id_join(data->tokkens, tokken->id);
	if (tab[1][0] == '\0' && tab[2] == NULL)
		data->last_return = 0;
	else
		data->last_return = ms_cd(data, &tab[1]);
	ft_free_strtab(tab);
}

void	do_exit(t_ms_data *data, t_one_data *o_data)
{
	char	**tab;

	tab = tokken_id_join(data->tokkens, o_data->tokken->id);
	free_data(o_data);
	check_standard(3);
	ms_exit(data, tab);
	ft_free_strtab(tab);
}
