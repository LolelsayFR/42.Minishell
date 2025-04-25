/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:38:04 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/25 10:26:00 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	infile_access(char *infile)
{
	if (access(infile, F_OK) == -1)
		return (-2);
	if (access(infile, R_OK) == -1)
		return (-1);
	return (0);
}

int	outfile_access(char *outfile)
{
	if (access(outfile, F_OK) == -1)
		return (1);
	if (access(outfile, W_OK) == -1)
		return (-1);
	return (1);
}
