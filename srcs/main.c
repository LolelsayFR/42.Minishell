/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:44:37 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/03 14:28:57 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

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
	ms_exit(EXIT_SUCCESS, data);
	return (EXIT_SUCCESS);
}

t_ms_data	*minishell_data_init(t_ms_data *data, char **envp)
{
	data->env_var = ft_strtabdup_lst(envp);
	data->prefix = ft_strdup_lst(LANG_PREFIX);
	data->is_inited = TRUE;
	data->context = NULL;
	data->tokkens = NULL;
	ms_sig_init(data);
	return (NULL);
}

int	minishell_main_loop(t_ms_data *data)
{
	data->is_running = TRUE;
	while (data->is_running == TRUE)
	{
		data->prompt = readline(ms_prefix(data));
		if (data->prompt == NULL)
			break ;
		if (data->prompt[0] != '\0')
			add_history(data->prompt);
		if (prompt_handler(data) == EXIT_SUCCESS)
			;
		else
			ft_printfd(2, LANG_PARS_ERROR, ms_prefix(data), data->prompt);
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
