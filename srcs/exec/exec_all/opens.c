/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opens.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:00:40 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/18 08:48:59 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	outfile_open(int outfile, int type, char *file)
{
	if (outfile != 1 && outfile != -1)
		close(outfile);
	if (type == OUTF_A)
		outfile = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (type == OUTF_R)
		outfile = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (outfile == -1)
		return (-2);
	return (outfile);
}

int	infile_open(int infile, int type, char *file)
{
	if (infile != 0 && infile != -1)
		close(infile);
	infile = open(file, O_RDONLY);
	if (infile == -1)
		return (-2);
	if (type == H_D)
		unlink(file);
	return (infile);
}
