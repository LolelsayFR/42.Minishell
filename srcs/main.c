/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:44:37 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/25 16:38:39 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.function.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms_data	*data;

	data = ms_get_data();
	if (data == NULL)
		return (EXIT_FAILURE);
	dumb(0, argc, argv);
	minishell_data_init(data, envp);
	if (data->is_inited == TRUE)
		minishell_main_loop(data);
	ft_alist_free();
	return (EXIT_SUCCESS);
}

t_ms_data	*minishell_data_init(t_ms_data *data, char **envp)
{
	dumb(0, envp);
	data->prefix = ft_strdup_lst(LANG_PREFIX);
	data->is_inited = TRUE;
	ms_sig_init(data);
	return (NULL);
}

int	minishell_main_loop(t_ms_data *data)
{
	data->is_running = TRUE;
	while (data->is_running == TRUE)
	{
		data->prompt = readline(ms_prefix(data));
		add_history(data->prompt);
		ft_printfd(1, "The prompt is : %s\n", data->prompt);
		if (!ft_strncmp(data->prompt, "exit", 5))
			data->is_running = FALSE;
	}
	return (EXIT_SUCCESS);
}

t_ms_data	*ms_get_data(void)
{
	static t_ms_data	*data = NULL;

	if (data == NULL)
		ft_alist_add_back(data = ft_calloc(1, sizeof(t_ms_data)));
	if (data == NULL)
		return (NULL);
	return (data);
}
