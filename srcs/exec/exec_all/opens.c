/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opens.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:00:40 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/22 13:31:11 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	outfile_open(int outfile, int type, char *file)
{
	if (outfile != 1 && outfile != -1 && outfile != -2)
		close(outfile);
	if (outfile_access(file) == -1)
		return (-2);
	if (type == OUTF_A)
	{
		outfile = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (outfile == -1)
			return (-2);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	else if (type == OUTF_R)
	{
		outfile = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (outfile == -1)
			return (-2);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	return (outfile);
}

int	infile_open(int infile, int type, char *file)
{
	if (infile != 0 && infile != -1 && infile != -2)
		close(infile);
	if (infile_access(file) == -1)
		return (-2);
	infile = open(file, O_RDONLY);
	if (infile == -1)
		return (-2);
	dup2(infile, STDIN_FILENO);
	close(infile);
	if (type == H_D)
		unlink(file);
	return (infile);
}
