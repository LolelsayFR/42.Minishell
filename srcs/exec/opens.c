/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opens.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:00:40 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/10 08:55:55 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

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
		while (1)
		{
			buff = malloc(5 * sizeof(char));
			if (read(outfile, buff, 5) != 0)
			{
				free(buff);
				break ;
			}
			free(buff);
		}
	}
	else if (type == OUTF_R)
		outfile = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	return (outfile);
}

int	infile_open(int infile, int type, char *file)
{
	if (type == OUTF_A || type == OUTF_R)
		return (infile);
	if (infile != -1)
		close(infile);
	infile = open(file, O_RDONLY);
	return (infile);
}

int	files_access(t_list *tokkens)
{
	t_list		*temp;
	t_ms_tokken	*tokken;

	temp = tokkens;
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->type == INF || tokken->type == H_D)
			if (infile_access(tokken->content) == -1)
				return (-1);
		if (tokken->type == OUTF_A || tokken->type == OUTF_R)
			if (outfile_access(tokken->content) == -1)
				return (-1);
		temp = temp->next;
	}
	return (0);
}
