/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:44:37 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/24 11:14:17 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms_data	*data;

	dumb(0, argc, argv);
	data = ms_get_data();
	if (data == NULL)
		return (EXIT_FAILURE);
	minishell_data_init(data, envp);
	data->is_running = true;
	if (data->is_inited == true)
		minishell_main_loop(data);
	ft_putstr_fd("exit\n", 2);
	ms_close(data->last_return, data);
	return (EXIT_SUCCESS);
}

t_ms_data	*minishell_data_init(t_ms_data *data, char **envp)
{
	data->init_pwd = getcwd(NULL, 0);
	data->cur_pwd = getcwd(NULL, 0);
	data->env_lst = env_to_lst(envp);
	data->env_var = env_to_tab(data->env_lst);
	env_export(ft_strdup("PWD="), getcwd(NULL, 0), &data->env_lst);
	env_export(ft_strdup("SHLVL="),
		ft_itoa(ft_atoi(getenv("SHLVL")) + 1), &data->env_lst);
	env_export(ft_strdup("LD_LIBRARY_PATH="),
		ft_strdupnull(getenv("LD_LIBRARY_PATH")), &data->env_lst);
	env_export(ft_strdup("PATH="),
		ft_strdupnull(getenv("PATH")), &data->env_lst);
	env_export(ft_strdup("_="), ft_strdupnull(getenv("_")), &data->env_lst);
	data->prefix = LANG_PREFIX;
	data->is_inited = true;
	ft_alist_add_front(data->context = ft_calloc(1, sizeof(t_ms_context)));
	data->tokkens = NULL;
	ms_sig_init(data);
	data->context->rl_redisplay = true;
	return (NULL);
}

int	minishell_main_loop(t_ms_data *data)
{
	while (data->is_running == true)
	{
		free(data->prompt);
		data->prompt = readline(ms_prefix(data));
		if (data->prompt == NULL)
			break ;
		if (data->prompt[0] != '\0' && ft_str_is_space(data->prompt) == false)
			add_history(data->prompt);
		else
			continue ;
		if (prompt_handler(data) == EXIT_SUCCESS && !data->context->hd_ctrl_c)
		{
			data->context->rl_redisplay = false;
			signal(SIGQUIT, exec_sig);
			if (find_nb_pipe(data->tokkens) == 0)
				exec_one(data, data->tokkens);
			else
				ms_exec(data, data->tokkens);
			data->context->rl_redisplay = true;
			signal(SIGQUIT, SIG_IGN);
		}
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
	free(data->prompt);
	free(data->cur_pwd);
	free(data->init_pwd);
	ft_free_strtab(data->env_var);
	free_env(data->env_lst);
	if (data->tokkens != NULL)
		(ft_lstclear(&data->tokkens, tokken_destructor), data->context = NULL);
	ft_alist_free();
	exit((unsigned char)exit_value);
}
