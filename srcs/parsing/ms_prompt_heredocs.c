/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_heredocs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:00:48 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/22 17:29:58 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static char	*heredoc_expand(char *str)
{
	t_pars_args	arg;

	ft_bzero(&arg, sizeof(t_pars_args));
	while (str[0] && str[arg.i])
	{
		if (str[arg.i] == '"' && arg.quote % 2 == 0)
			arg.d_quote++;
		else if (str[arg.i] == '\'' && arg.d_quote % 2 == 0)
			arg.quote++;
		else if (str[++arg.i - 1] == '$' && (str[arg.i] == '?'
				|| str[arg.i] == '_'
				|| str[arg.i] == '$' || ft_isalnum(str[arg.i])))
			arg.i += var_placer(&str, &arg);
	}
	return (ft_strdup(str));
}

static char	*heredoc_unquote(char *str)
{
	t_pars_args	arg;

	ft_bzero(&arg, sizeof(t_pars_args));
	if (str[0] == '$' && str[1] == '\0')
		return (str);
	while (str[arg.i])
	{
		if (str[arg.i] == '"' && arg.quote % 2 == 0)
		{
			str = pars_injector(str, NULL, &arg);
			arg.d_quote++;
		}
		else if (str[arg.i] == '\'' && arg.d_quote % 2 == 0)
		{
			str = pars_injector(str, NULL, &arg);
			arg.quote++;
		}
		else if (str[arg.i] == '$' && ft_strchr("\"'", str[arg.i + 1])
			&& (arg.d_quote + arg.quote) % 2 == 0)
			str = pars_injector(str, NULL, &arg);
		arg.i++;
	}
	return (str);
}

static void	heredoc_loop(t_ms_tokken **tok, char *eof, int fd)
{
	char	*hdp;
	char	*expand;

	hdp = NULL;
	ms_get_data()->context->last_fd = dup(STDIN_FILENO);
	while (true)
	{
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
		expand = heredoc_expand(hdp);
		ft_putendl_fd(expand, fd);
		free(expand);
	}
	close(fd);
	dup2(ms_get_data()->context->last_fd, STDIN_FILENO);
	free(eof);
}

void	heredoc_initer(t_ms_data *data, t_ms_tokken	**tokken)
{
	char	*name;
	char	*tmp;

	data->context->heredocs++;
	signal(SIGINT, heredoc_sig);
	name = ft_strdup("/tmp/ms_hd_");
	tmp = ft_itoa(data->context->heredocs);
	ft_strcat(&name, tmp);
	free(tmp);
	tmp = ft_strjoin(data->init_pwd, name);
	free(name);
	heredoc_loop(tokken, heredoc_unquote((*tokken)->content),
		open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	(*tokken)->content = tmp;
	ms_sig_init(ms_get_data());
}
