/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:26:58 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/04 12:20:28 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

void	print_files(t_files *files)
{
	t_files	*temp;

	temp = files;
	while (temp != NULL)
	{
		printf("%d\t%d\n", temp->fd, temp->file_t);
		temp = temp->next;
	}
}

void	print_pids(t_pids *pids)
{
	t_pids	*temp;

	temp = pids;
	while (temp != NULL)
	{
		printf("%d\n", temp->pid);
		temp = temp->next;
	}
}
