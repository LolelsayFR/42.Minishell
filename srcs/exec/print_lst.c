/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:26:58 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/10 10:19:16 by artgirar         ###   ########.fr       */
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
