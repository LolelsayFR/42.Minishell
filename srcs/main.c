/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:44:37 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/14 14:51:14 by emaillet         ###   ########.fr       */
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
	if (data->is_inited == true)
		minishell_main_loop(data);
	ms_close(data->last_return, data);
	return (EXIT_SUCCESS);
}

t_ms_data	*minishell_data_init(t_ms_data *data, char **envp)
{
	data->env_lst = env_to_lst(envp);
	data->env_var = env_to_tab(data->env_lst);
	data->prefix = ft_strdup_lst(LANG_PREFIX);
	data->is_inited = true;
	ft_alist_add_front(data->context = ft_calloc(1, sizeof(t_ms_context)));
	data->tokkens = NULL;
	ms_sig_init(data);
	return (NULL);
}

int	minishell_main_loop(t_ms_data *data)
{
	data->is_running = true;
	while (data->is_running == true)
	{
		data->prompt = readline(ms_prefix(data));
		if (data->prompt == NULL)
			break ;
		if (data->prompt[0] != '\0' && ft_str_is_space(data->prompt) == false)
			add_history(data->prompt);
		else
			continue ;
		if (prompt_handler(data) == EXIT_SUCCESS)
			ms_exec(data, data->tokkens);
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

void	ms_close(unsigned char exit_value, t_ms_data *data)
{
	ft_free_strtab(data->env_var);
	free_env(data->env_lst);
	if (data->tokkens != NULL)
		(ft_lstclear(&data->tokkens, tokken_destructor), data->context = NULL);
	ft_alist_free();
	exit((unsigned char)exit_value);
}
