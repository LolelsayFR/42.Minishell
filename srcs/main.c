/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:44:37 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/21 17:39:26 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.include.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms_data	*data;

	dumb(0, argc, argv);
	ft_alist_add_back(data = ft_calloc(1, sizeof(t_ms_data)));
	if (!data)
		return (EXIT_ERROR);
	minishell_data_init(data, envp);
	if (data->is_inited == TRUE)
		minishell_main_loop(data);
	ft_alist_free();
	return (EXIT_SUCCESS);
}

t_ms_data	*minishell_data_init(t_ms_data *data, char **envp)
{
	dumb(0, envp);
	data->is_inited = TRUE;
	return (NULL);
}

int	minishell_main_loop(t_ms_data *data)
{
	data->is_running = TRUE;
	while (data->is_running == TRUE)
	{
		data->prompt = readline("\e[48;2;20;100;20;1m MINI MICHEL ⤵ \e[0m\n");
		add_history(data->prompt);
		ft_printfd(1, "The prompt is : %s\n", data->prompt);
		if (!ft_strncmp(data->prompt, "exit", 5))
			data->is_running = FALSE;
	}
	return (EXIT_SUCCESS);
}
