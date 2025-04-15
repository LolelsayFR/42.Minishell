/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:00:48 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/15 09:41:28 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	heredoc_initer(t_ms_data *data)
{
	int		fd;
	char	*name;
	char	*tmp;

	data->context->heredocs++;
	name = ft_strdup("/tmp/ms_hd_");
	tmp = ft_itoa(data->context->heredocs);
	ft_strcat(&name, tmp);
	free(tmp);
	tmp = ft_strjoin(data->init_pwd, name);
	fd = open(tmp, O_CREAT);
	free(tmp);
	free(name);
}

void	heredoc_finder(t_list *lst, t_ms_data *data)
{
	t_ms_tokken	*tokken;

	tokken = (t_ms_tokken *)lst->content;
	while (lst)
	{
		tokken = (t_ms_tokken *)lst->content;
		if (tokken->type == H_D)
			heredoc_initer(data);
		lst = lst->next;
	}
}
