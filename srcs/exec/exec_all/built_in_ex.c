/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:53:41 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/15 17:55:03 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

//To Do
void	do_echo(t_ms_data *data, t_ms_tokken *tokken)
{
	char	*str;

	str = tokken_join_id(data->tokkens, tokken->id);
	ms_echo(data, str, 0);
	free(str);
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
	(void)tab;
	//ms_export(data, tab);
	// ft_free_strtab(tab);
}

//To Do
void	do_cd(t_ms_data *data, t_ms_tokken *tokken)
{
	char	*str;

	str = tokken_join_id(data->tokkens, tokken->id);
	printf("%s\n", str);
	ms_cd(data, str);
	free(str);
}

void	do_exit(t_ms_data *data, t_ms_tokken *tokken)
{
	(void)data;
	(void)tokken;
	ms_exit(data, NULL);
}
