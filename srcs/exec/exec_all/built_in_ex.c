/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:53:41 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/15 11:26:37 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	do_echo(t_ms_data *data, t_ms_tokken *tokken)
{
	char	*str;

	str = tokken_join_id(data->tokkens, tokken->id);
	ms_echo(data, str, 0);
	free(str);
}

void	do_unset(t_ms_data *data, t_ms_tokken *tokken)
{
	char	*str;

	str = tokken_join_id(data->tokkens, tokken->id);
	ms_unset(data, str);
	free(str);
}

void	do_export(t_ms_data *data, t_ms_tokken *tokken)
{
	char	**tab;

	tab = tokken_id_join(data->tokkens, tokken->id);
	//ms_export(data, tab);
	ft_free_strtab(tab);
}

void	do_cd(t_ms_data *data, t_ms_tokken *tokken)
{
	(void)data;
	(void)tokken;
}

void	do_exit(t_ms_data *data, t_ms_tokken *tokken)
{
	(void)data;
	(void)tokken;
	ms_exit(data, NULL);
}
