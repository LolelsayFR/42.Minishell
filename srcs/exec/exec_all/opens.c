/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opens.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:00:40 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/10 10:30:24 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	outfile_open(int outfile, int type, char *file)
{
	char	*buff;

	if (type == INF || type == H_D)
		return (outfile);
	if (outfile != -1)
		close(outfile);
	if (type == OUTF_A)
	{
		outfile = open(file, O_CREAT | O_WRONLY, 0644);
		if (outfile == -1)
			return (-2);
		while (1)
		{
			buff = malloc(5 * sizeof(char));
			if (read(outfile, buff, 5) != 0)
				return (free(buff), outfile);
			free(buff);
		}
	}
	else if (type == OUTF_R)
		outfile = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (outfile == -1)
		return (-2);
	return (outfile);
}

int	infile_open(int infile, int type, char *file)
{
	if (type == OUTF_A || type == OUTF_R)
		return (infile);
	if (infile != -1)
		close(infile);
	infile = open(file, O_RDONLY);
	if (infile == -1)
		return (-2);
	return (infile);
}
