/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:00:48 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/15 14:40:37 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static void	heredoc_loop(t_ms_data *data, t_ms_tokken **tok, t_list **lst)
{
	char	*hdp;

	hdp = NULL;
	while (true)
	{
		hdp = readline(">");
		ft_lstadd_back(lst, ft_lstnew(ft_strdup(hdp)));
		ft_strcat(&(data->prompt), "\n");
		ft_strcat(&(data->prompt), hdp);
		if (!ft_strcmp(hdp, (*tok)->content) && hdp != NULL)
			break ;
		if (hdp == NULL)
		{
			(*tok)->flag = CTRL_D_HD;
			break ;
		}
	}
}

static void	ms_putherdoc(char *str)
{
	ft_putendl_fd(str, ms_get_data()->context->last_fd);
}

static void	heredoc_initer(t_ms_data *data, t_ms_tokken	**tokken)
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
	lst = NULL;
	heredoc_loop(data, tokken, &lst);
	data->context->last_fd = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	ft_lstiter(lst, (void *)ms_putherdoc);
	ft_lstprintfd(lst, 2);
	if ((*tokken)->flag == CTRL_D_HD)
		ft_printfd(2, HDW, ms_prefix(ms_get_data()),
			8, HDWT, (*tokken)->content);
	free((*tokken)->content);
	(*tokken)->content = tmp;
	close(data->context->last_fd);
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
