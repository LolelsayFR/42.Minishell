/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:00:48 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/24 08:43:18 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static char	*heredoc_expand(char **str, int flag)
{
	t_pars_args	arg;

	ft_bzero(&arg, sizeof(t_pars_args));
	if (ms_get_data()->context->hd_is_expand > 0 || flag == EMPTY_QUOTE)
		return (*str);
	while (*str != NULL && (*str)[arg.i])
	{
		if ((*str)[arg.i] == '$')
			arg.i += var_placer(str, &arg, true);
		arg.i++;
	}
	return (*str);
}

static char	*heredoc_unquote(char *str)
{
	t_pars_args	arg;

	ft_bzero(&arg, sizeof(t_pars_args));
	while (str[arg.i])
	{
		if (str[arg.i] == '"' && arg.quote % 2 == 0)
		{
			arg.d_quote++;
			ms_get_data()->context->hd_is_expand++;
			str = pars_injector(str, NULL, &arg);
		}
		else if (str[arg.i] == '\'' && arg.d_quote % 2 == 0)
		{
			arg.quote++;
			ms_get_data()->context->hd_is_expand++;
			str = pars_injector(str, NULL, &arg);
		}
		else if (str[arg.i] == '$' && (arg.d_quote + arg.quote) % 2 == 0)
			str = pars_injector(str, NULL, &arg);
		arg.i++;
	}
	return (str);
}

static void	heredoc_loop(t_ms_tokken **tok, char *eof, int fd)
{
	char	*hdp;

	hdp = NULL;
	while (true)
	{
		free(hdp);
		hdp = readline(">");
		if (!ft_strcmp(hdp, eof) && hdp != NULL)
			break ;
		if (hdp == NULL && !ms_get_data()->context->hd_ctrl_c)
		{
			ft_printfd(2, HDW, ms_prefix(ms_get_data()), eof);
			(*tok)->flag = CTRL_D_HD;
			break ;
		}
		else if (ms_get_data()->context->hd_ctrl_c)
			break ;
		heredoc_expand(&hdp, (*tok)->flag);
		ft_putendl_fd(hdp, fd);
	}
	free(hdp);
	close(fd);
	free(eof);
}

void	heredoc_initer(t_ms_data *data, t_ms_tokken	**tokken)
{
	char	*name;
	char	*tmp;

	data->context->heredocs++;
	signal(SIGINT, heredoc_sig);
	data->context->temp_hd_fd = dup(STDIN_FILENO);
	name = ft_strdup("/tmp/ms_hd_");
	tmp = ft_itoa(data->context->heredocs);
	ft_strcat(&name, tmp);
	free(tmp);
	tmp = ft_strjoin(data->init_pwd, name);
	free(name);
	heredoc_loop(tokken, heredoc_unquote((*tokken)->content),
		open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	(*tokken)->content = tmp;
	if (data->context->hd_ctrl_c == true)
		dup2(data->context->temp_hd_fd, STDIN_FILENO);
	close(data->context->temp_hd_fd);
	ms_sig_init(data);
}
