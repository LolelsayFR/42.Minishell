/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:53:41 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/16 13:25:06 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

//To Do
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

//To Do
void	do_unset(t_ms_data *data, t_ms_tokken *tokken)
{
	int		i;
	char	**tab;

	i = 0;
	tab = tokken_id_join(data->tokkens, tokken->id);
	free(tab[i++]);
	while (tab[i] != NULL)
	{
		//ms_unset(data, tab);
		free(tab[i]);
		i++;
	}
	free(tab);
}

//To Do
void	do_export(t_ms_data *data, t_ms_tokken *tokken)
{
	char	**tab;

	tab = tokken_id_join(data->tokkens, tokken->id);
	ms_export(data, &tab[1]);
	ft_free_strtab(tab);
}

//To Do
void	do_cd(t_ms_data *data, t_ms_tokken *tokken)
{
	char	**tab;

	tab = tokken_id_join(data->tokkens, tokken->id);
	data->last_return = ms_cd(data, &tab[1]);
	ft_free_strtab(tab);
}

void	do_exit(t_ms_data *data, t_ms_tokken *tokken)
{
	char	**tab;

	tab = tokken_id_join(data->tokkens, tokken->id);
	ms_exit(data, tab);
	ft_free_strtab(tab);
}
