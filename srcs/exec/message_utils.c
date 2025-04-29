/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:14:38 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/29 14:38:16 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	no_permission(char *str)
{
	ft_printfd(2, EXEC_NOPERM, ms_prefix(ms_get_data()), str);
}

void	bad_dir(char *str)
{
	ft_printfd(2, EXEC_NODIR, ms_prefix(ms_get_data()), str);
}

void	ambigous(char *str)
{
	ft_printfd(2, "%s: %s: ambiguous redirect\n", ms_prefix(ms_get_data()),
		str);
}

int	error_filing(t_ex_data *ex_data, t_ms_tokken *tokken)
{
	if ((ex_data->file[0] == -2 || ex_data->file[1] == -2)
		&& tokken->type != CMD && tokken->type != B_IN)
		return (bad_dir(tokken->content), -1);
	else if ((ex_data->file[0] == -1 || ex_data->file[1] == -1)
		&& tokken->type != CMD && tokken->type != B_IN)
		return (no_permission(tokken->content), -1);
	return (0);
}
