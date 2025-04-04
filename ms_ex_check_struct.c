/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ex_check_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:29:57 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/04 09:31:03 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

t_files	*new_files(void)
{
	t_files	*files;

	files = malloc(sizeof(t_files));
	files->next = NULL;
	return (files);
}
