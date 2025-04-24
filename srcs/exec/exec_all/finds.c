/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:07:48 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/24 15:11:00 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	infile_rights(char *file)
{
	if (access(file, F_OK | R_OK) == -1)
		return (-1);
	return (0);
}

static int	outfile_rights(char *file)
{
	if (access(file, F_OK | W_OK) == -1)
		return (-1);
	return (0);
}

void	are_files_good(t_ms_data *data, t_ex_data *ex_data)
{
	int			i;
	int			id;
	t_ms_tokken	*tokken;
	t_list		*temp;

	i = 0;
	id = ex_data->tokken->id;
	temp = first_in_id(data->tokkens, ex_data->tokken->id);
	tokken = temp->content;
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->id != id)
			break ;
		if (tokken->type == H_D || tokken->type == INF)
			i = infile_rights(tokken->content);
		else if (tokken->type == OUTF_A || tokken->type == OUTF_R)
			i = outfile_rights(tokken->content);
		if (i == -1)
			break ;
		temp = temp->next;
	}
	data->last_return = 0;
	if (i == -1)
		ft_printfd(2, "%s: Permission Denied\n", tokken->content);
}

int	find_nb_pipe(t_list *tokkens)
{
	t_list		*temp;
	t_ms_tokken	*tokken;

	temp = tokkens;
	while (temp->next != NULL)
		temp = temp->next;
	tokken = temp->content;
	return (tokken->id);
}

int	find_nb_cmd(t_list *tokkens)
{
	int			i;
	t_list		*temp;
	t_ms_tokken	*tokken;

	i = 0;
	temp = tokkens;
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->type == CMD || tokken->type == B_IN)
			i++;
		temp = temp->next;
	}
	return (i);
}
