/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokken_printer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:26:23 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/07 16:01:06 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static void	print_tokken(t_ms_tokken *tokken)
{
	printf("\nTokken id = %d\nType : %d\nContent = %s\n\n", tokken->id,
		tokken->type, tokken->content);
}

void	print_all_tokken(t_list *lst_head)
{
	t_ms_tokken	*tokken;
	t_list		*lst;

	lst = lst_head;
	while (lst)
	{
		tokken = lst->content;
		print_tokken(tokken);
		lst = lst->next;
	}
}
