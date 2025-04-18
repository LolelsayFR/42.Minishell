/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_standard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:55:21 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/18 14:08:15 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	check_standard(int i)
{
	static int	standard[2];

	if (i == 0)
	{
		standard[0] = dup(STDIN_FILENO);
		standard[1] = dup(STDOUT_FILENO);
	}
	else if (i == 1)
	{
		dup2(standard[0], STDIN_FILENO);
		close(standard[0]);
	}
	else if (i == 2)
	{
		dup2(standard[1], STDOUT_FILENO);
		close(standard[1]);
	}
	else if (i == 3)
	{
		dup2(standard[0], STDIN_FILENO);
		dup2(standard[1], STDOUT_FILENO);
		double_close(standard[0], standard[1]);
	}
}
