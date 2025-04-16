/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:00:48 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/16 12:23:32 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static void	heredoc_loop(t_ms_tokken **tok, t_list **lst, char *eof)
{
	char	*hdp;

	hdp = NULL;
	while (true)
	{
		hdp = readline(">");
		if (!ft_strcmp(hdp, eof) && hdp != NULL)
			break ;
		if (hdp == NULL)
		{
			ft_printfd(2, HDW, ms_prefix(ms_get_data()), eof);
			(*tok)->flag = CTRL_D_HD;
			break ;
		}
		ft_lstadd_back(lst, ft_lstnew(ft_strdup(hdp)));
	}
	free(eof);
}

static void	ms_putherdoc(char *str)
{
	ft_putendl_fd(str, ms_get_data()->context->last_fd);
}

void	heredoc_initer(t_ms_data *data, t_ms_tokken	**tokken)
{
	char	*name;
	char	*tmp;
	t_list	*lst;

	data->context->heredocs++;
	name = ft_strdup("/tmp/ms_hd_");
	tmp = ft_itoa(data->context->heredocs);
	ft_strcat(&name, tmp);
	free(tmp);
	tmp = ft_strjoin(data->init_pwd, name);
	free(name);
	lst = NULL;
	heredoc_loop(tokken, &lst, str_unquote((*tokken)->content));
	data->context->last_fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	ft_lstiter(lst, (void *)ms_putherdoc);
	(*tokken)->content = tmp;
	close(data->context->last_fd);
	ft_lstclear(&lst, free);
}
