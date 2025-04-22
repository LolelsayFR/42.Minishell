/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:49:29 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/22 13:18:07 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	find_files(t_one_data *o_data, t_list *tokkens)
{
	t_ms_tokken	*tokken;

	while (tokkens != NULL)
	{
		tokken = tokkens->content;
		if (tokken->type == INF || tokken->type == H_D)
			find_one_infile(o_data, tokken);
		else if (tokken->type == OUTF_R || tokken->type == OUTF_A)
			find_one_outfile(o_data, tokken);
		if (o_data->inf == -1 || o_data->outf == -1)
			return (ft_printfd(2, "%s: No such file or directory\n",
					tokken->content), -1);
		tokkens = tokkens->next;
	}
	return (0);
}

void	find_one_infile(t_one_data *o_data, t_ms_tokken *tokken)
{
	if (o_data->inf != 0)
		close(o_data->inf);
	if (infile_access(tokken->content) == -1)
	{
		o_data->inf = -1;
		return ;
	}
	o_data->inf = infile_open(o_data->inf, tokken->type, tokken->content);
	dup2(o_data->inf, STDIN_FILENO);
	if (o_data->inf == -2)
		o_data->inf = -1;
}

void	find_one_outfile(t_one_data *o_data, t_ms_tokken *tokken)
{
	if (o_data->outf != 1)
		close(o_data->outf);
	if (outfile_access(tokken->content) == -1)
	{
		o_data->outf = -1;
		return ;
	}
	o_data->outf = outfile_open(o_data->outf, tokken->type, tokken->content);
	dup2(o_data->outf, STDOUT_FILENO);
	if (o_data->outf == -2)
		o_data->outf = -1;
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
	if (infile != 0)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != 1)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
}
