/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:44:37 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/21 13:52:42 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.include.h"
#include <readline/history.h>

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
	ft_lstclear(&data->prompts, nufree);
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
		ft_printfd(1, "\e[48;2;20;100;20;1m MINI MICHEL ⤵ \e[0m\n");
		ft_lstadd_front(&data->prompts, ft_lstnew(readline(NULL)));
		add_history(data->prompts->content);
		ft_printfd(1, "The prompt is : %s\n", data->prompts->content);
		if (!ft_strncmp(data->prompts->content, "exit", 5))
			data->is_running = FALSE;
	}
	ft_putlst_fd_prefix(data->prompts, 1, "Prompts = ");
	return (EXIT_SUCCESS);
}
