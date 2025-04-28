/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:23:31 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/28 10:33:24 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

char	**tokken_id_join(t_list *tokkens, int id)
{
	int			i;
	char		**cmd;
	t_list		*temp;
	t_ms_tokken	*tokken;

	i = 0;
	temp = first_in_id(tokkens, id);
	cmd = ft_calloc((arg_nb(temp, id) + 1), sizeof(char *));
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->id != id)
			break ;
		if (tokken->type == CMD || tokken->type == ARG
			|| tokken->type == B_IN)
			cmd[i++] = ft_strdup(tokken->content);
		temp = temp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
