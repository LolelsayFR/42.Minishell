/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:53:41 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/16 08:52:59 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

//To Do
void	do_echo(t_ms_data *data, t_ms_tokken *tokken)
{
	char	*str;
	char	**tab;

	tab = tokken_id_join(data->tokkens, tokken->id);
	if (ms_ft_strncmp(tab[1], "-n\0", 3) == 0)
	{
		str = ft_strjointab(&tab[2]);
		ms_echo(data, str, 1);
	}
	else
	{
		str = ft_strjointab(&tab[1]);
		ms_echo(data, str, 0);
	}
	free(str);
	ft_free_strtab(tab);
}

//To Do
void	do_unset(t_ms_data *data, t_ms_tokken *tokken)
{
	char	*str;

	str = tokken_join_id(data->tokkens, tokken->id);
	ms_unset(data, str);
	free(str);
}

//To Do
void	do_export(t_ms_data *data, t_ms_tokken *tokken)
{
	char	**tab;

	tab = tokken_id_join(data->tokkens, tokken->id);
	ms_export(data, tab);
	ft_free_strtab(tab);
}

//To Do
void	do_cd(t_ms_data *data, t_ms_tokken *tokken)
{
	char	**tab;

	tab = tokken_id_join(data->tokkens, tokken->id);
	ms_cd(data, tab);
}

void	do_exit(t_ms_data *data, t_ms_tokken *tokken)
{
	(void)data;
	(void)tokken;
	ms_exit(data, NULL);
}
