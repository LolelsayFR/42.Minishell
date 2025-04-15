/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:23:31 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/15 11:25:36 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

char	*tokken_join_id(t_list *tokkens, int id)
{
	char		*str;
	t_ms_tokken	*tokken;
	t_list		*temp;

	temp = tokkens;
	tokken = temp->content;
	while (temp != NULL && tokken->id != id)
	{
		temp = temp->next;
		tokken = temp->content;
	}
	str = NULL;
	while (temp != NULL && tokken->id == id)
	{
		if (tokken->type == ARG)
			ft_strcat(&str, tokken->content);
		temp = temp->next;
		if (temp == NULL)
			break ;
		tokken = temp->content;
	}
	return (str);
}

char	**tokken_id_join(t_list *tokkens, int id)
{
	int			i;
	char		**cmd;
	t_list		*temp;
	t_ms_tokken	*tokken;

	i = 0;
	temp = first_in_id(tokkens, id);
	cmd = malloc((arg_nb(temp, id) + 1) * sizeof(char *));
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->id != id)
			break ;
		if (tokken->type == CMD || tokken->type == ARG)
			cmd[i++] = tokken->content;
		temp = temp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
