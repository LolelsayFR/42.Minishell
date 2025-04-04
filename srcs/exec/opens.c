/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opens.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:00:40 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/04 10:37:41 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

void	file_error(t_files *files)
{
	files->file_t = -1;
}

void	outfile_open(t_ms_tokken *tokken, t_files *files)
{
	int	fd;

	if (access(tokken->content, F_OK) == -1)
		return (file_error(files));
	if (access(tokken->content, W_OK) == -1)
		return (file_error(files));
	if (tokken->type == OUTF_R)
		fd = open(tokken->content, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (tokken->type == OUTF_A)
	{
		fd = open(tokken->content, O_CREAT | O_WRONLY, 0644);
		while (read(fd, NULL, 5) != 0)
			;
	}
	files->fd = fd;
}

void	infile_open(t_ms_tokken *tokken, t_files *files)
{
	int	fd;

	if (access(tokken->content, F_OK) == -1)
		return (file_error(files));
	if (access(tokken->content, R_OK) == -1)
		return (file_error(files));
	fd = open(tokken->content, O_RDONLY);
	files->fd = fd;
}

t_files	*open_all(t_list *tokkens)
{
	t_files		*files;
	t_list		*temp;
	t_ms_tokken	*tokken;

	files = malloc(sizeof(t_files));
	files->next = NULL;
	temp = tokkens;
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->type == OUTF_R || tokken->type == OUTF_A)
		{
			outfile_open(tokken, files);
			files = files->next;
		}
		else if (tokken->type == INF || tokken->type == H_D)
		{
			infile_open(tokken, files);
			files = files->next;
		}
		temp = temp->next;
	}
	return (files);
}
