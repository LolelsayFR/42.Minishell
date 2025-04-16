/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:49:29 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/16 13:53:34 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	find_one_infile(t_list *tokkens)
{
	t_ms_tokken	*tokken;
	int			infile;

	infile = 0;
	while (tokkens != NULL)
	{
		tokken = tokkens->content;
		if (tokken->type == INF || tokken->type == H_D)
		{
			if (infile != 0)
				close(infile);
			infile = infile_open(infile, tokken->type, tokken->content);
			if (infile == -2)
				return (-1);
		}
		tokkens = tokkens->next;
	}
	return (infile);
}

int	find_one_outfile(t_list *tokkens)
{
	t_ms_tokken	*tokken;
	int			outfile;

	outfile = 1;
	while (tokkens != NULL)
	{
		tokken = tokkens->content;
		if (tokken->type == OUTF_R || tokken->type == OUTF_A)
		{
			if (outfile != 1)
				close(outfile);
			outfile = outfile_open(outfile, tokken->type, tokken->content);
			if (outfile == -2)
				return (-1);
		}
		tokkens = tokkens->next;
	}
	return (outfile);
}

t_list	*find_cmd(t_list *tokkens)
{
	t_ms_tokken	*tokken;

	while (tokkens != NULL)
	{
		tokken = tokkens->content;
		if (tokken->type == CMD || tokken->type == B_IN)
			return (tokkens);
		tokkens = tokkens->next;
	}
	return (NULL);
}

void	choose_files(int infile, int outfile)
{
	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
}
