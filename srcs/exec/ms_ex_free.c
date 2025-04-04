/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:25:16 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/04 10:38:51 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

void    files_clear(t_files *files)
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
