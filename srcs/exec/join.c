/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:23:31 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/29 14:11:21 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	arg_in_id(t_list *tokkens, int id)
{
	int			i;
	int			j;
	char		**temp;
	t_ms_tokken	*tokken;

	i = 0;
	while (tokkens != NULL)
	{
		tokken = tokkens->content;
		if (tokken->id != id)
			break ;
		if (tokken->flag == ISEXPAND)
		{
			j = 0;
			temp = ft_split(tokken->content, ' ');
			while (temp[j++] != NULL)
				i++;
			ft_free_strtab(temp);
		}
		else
			i++;
		tokkens = tokkens->next;
	}
	return (i);
}

static void	add_tab_in_tab(char **cmd, char *content, int *i)
{
	int		j;
	char	**temp;

	j = 0;
	temp = ft_split(content, ' ');
	while (temp[j] != NULL)
	{
		cmd[*i] = ft_strdup(temp[j]);
		(*i)++;
		j++;
	}
	ft_free_strtab(temp);
}

char	**tokken_id_join(t_list *tokkens, int id)
{
	int			i;
	char		**cmd;
	t_list		*temp;
	t_ms_tokken	*tokken;

	i = 0;
	temp = first_in_id(tokkens, id);
	cmd = malloc((arg_in_id(temp, id) + 1) * sizeof(char *));
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->id != id)
			break ;
		if ((tokken->type == CMD || tokken->type == ARG
				|| tokken->type == B_IN) && tokken->flag == ISEXPAND)
			add_tab_in_tab(cmd, tokken->content, &i);
		else if (tokken->type == CMD || tokken->type == ARG
			|| tokken->type == B_IN)
			cmd[i++] = ft_strdup(tokken->content);
		temp = temp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
