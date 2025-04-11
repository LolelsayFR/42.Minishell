/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ex_check_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:29:57 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/11 09:19:20 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"
#include "exec.h"

int	arg_nb(t_list *tokkens, int id)
{
	int			i;
	t_list		*temp;
	t_ms_tokken	*tokken;

	i = 0;
	temp = tokkens;
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->id != id)
			return (i);
		temp = temp->next;
	}
	return (i);
}

char	**tokken_id_join(t_list *tokkens, int id)
{
	int			i;
	char		**cmd;
	t_list		*temp;
	t_ms_tokken	*tokken;

	i = 0;
	temp = first_in_id(tokkens, id);
	cmd = malloc((arg_nb(temp, id) + 3) * sizeof(char *));
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
	print_tab(cmd);
	return (cmd);
}

t_list	*first_in_id(t_list *tokkens, int id)
{
	t_list		*temp;
	t_ms_tokken	*tokken;

	temp = tokkens;
	while (temp != NULL)
	{
		tokken = temp->content;
		if (tokken->id == id)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_pipe	*pipe_init(void)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	pipe->pipe[0] = 0;
	pipe->pipe[1] = 1;
	pipe->next = NULL;
	return (pipe);
}

t_ex_data	*exec_init(t_list *tokkens)
{
	t_ex_data	*ex_data;

	ex_data = malloc(sizeof(t_ex_data));
	ex_data->nb_cmd = find_nb_cmd(tokkens);
	ex_data->pid = malloc(ex_data->nb_cmd * sizeof(int));
	ex_data->pipes = pipe_init();
	return (ex_data);
}
