/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:14:40 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/10 19:17:48 by emaillet         ###   ########.fr       */
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
	}
}

bool	ms_sig_init(t_ms_data *data)
{
	dumb(0, data);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ms_sig_handler);
	signal(SIGSEGV, ms_sig_handler);
	return (true);
}
