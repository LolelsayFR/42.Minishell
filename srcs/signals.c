/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:14:40 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/23 13:25:20 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static void	ms_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		ms_get_data()->last_return = 130;
		if (ms_get_data()->context->rl_redisplay)
			rl_redisplay();
	}
}

bool	ms_sig_init(t_ms_data *data)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ms_sig_handler);
	signal(SIGSEGV, ms_sig_handler);
	(void) data;
	return (true);
}

void	heredoc_sig(int sig)
{
	int	fd;

	if (sig == SIGINT)
	{
		fd = dup(STDIN_FILENO);
		ms_get_data()->context->hd_ctrl_c = true;
		dup2(fd, STDIN_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_printfd(2, "\n");
		ms_get_data()->last_return = 130;
		close(fd);
	}
}

void	exec_sig(int sig)
{
	int	fd;

	if (sig == SIGQUIT)
	{
		fd = dup(STDIN_FILENO);
		ms_get_data()->context->hd_ctrl_c = true;
		dup2(fd, STDIN_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_printfd(2, "Quit\n");
		ms_get_data()->last_return = 131;
		close(fd);
	}
}
