/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:14:40 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/07 15:41:17 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static void	ms_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printfd(1, "\n%s", ms_get_data()->prefix);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

bool	ms_sig_init(t_ms_data *data)
{
	dumb(0, data);
	signal(SIGQUIT, SIG_IGN);
	//signal(SIGINT, ms_sig_handler);
	signal(SIGSEGV, ms_sig_handler);
	return (true);
}
