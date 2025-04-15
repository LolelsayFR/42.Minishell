/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:00:48 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/15 12:12:32 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static void	heredoc_loop(t_ms_data *data, t_ms_tokken **tok, int fd)
{
	char	*hdp;

	hdp = NULL;
	printf("HEREDOC %d was created\nNeed [%s] for close [%d] fd\n", data->context->heredocs, (*tok)->content, fd);
	while (true)
	{
		hdp = readline(">");
		ft_putendl_fd(hdp, fd);
		if (!ft_strcmp(hdp, (*tok)->content) && hdp != NULL)
			break ;
		if (hdp == NULL)
		{
			(*tok)->flag = CTRL_D_HD;
			break ;
		}
	}
}

static void	heredoc_initer(t_ms_data *data, t_ms_tokken	**tokken)
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
	fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	heredoc_loop(data, tokken, fd);
	if ((*tokken)->flag == CTRL_D_HD)
		ft_printfd(2, HDW, ms_prefix(ms_get_data()),
			8, HDWT, (*tokken)->content);
	free((*tokken)->content);
	(*tokken)->content = tmp;
	close(fd);
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
			heredoc_initer(data, &tokken);
		lst = lst->next;
	}
}
