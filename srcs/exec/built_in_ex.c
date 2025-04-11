/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:53:41 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/11 20:01:00 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

void	do_echo(t_ms_data *data, t_ms_tokken *tokken)
{
	char	*str;

	str = tokken_join_id(data->tokkens, tokken->id);
	ms_echo(data, str);
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
	char	*str;

	str = tokken_join_id(data->tokkens, tokken->id);
	//ms_export(data, str);
	free(str);
	(void)data;
	(void)tokken;
	(void)str;
}
