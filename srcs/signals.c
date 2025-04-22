/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:14:40 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/22 08:50:21 by emaillet         ###   ########.fr       */
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
		rl_redisplay();
		ms_get_data()->last_return = 130;
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
	if (sig == SIGINT)
	{
		ms_get_data()->context->hd_ctrl_c = true;
		close(STDIN_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		ms_get_data()->last_return = 130;
	}

}
