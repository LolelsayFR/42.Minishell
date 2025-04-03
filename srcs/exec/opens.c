/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opens.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:00:40 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/03 10:37:33 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

void	files_clear(t_files *files)
{
		t_files	*temp;

		temp = files;
		while (temp != NULL)
		{
				close(temp->fd);
				temp = temp->next;
				free(files);
				files = temp;
		}
}

t_files	new_files()
{
		t_files	*files;

		files = malloc(sizeof(t_files));
		files->next = NULL;
		return (files);
}

t_files	open_all(t_list *tokkens)
{
		t_files	*files;
		t_list	*temp;

		files = malloc(sizeof(t_files));
		files->next = NULL;
		temp = tokkens;
		while (temp != NULL)
		{
				if (temp->content->type == OUTF_R || temp->content->type == OUTF_A)
				{
						files = outfile_open(temp->content);
						if (files == -1)
								return (files_clear(files), NULL);
						files = files_next;
				}
				temp = temp->next;
		}
		return (files);
}
