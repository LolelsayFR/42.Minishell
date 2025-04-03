/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:30:33 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/03 12:00:15 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	parsing_init(t_ms_data *data)
{	
	ft_alist_add_front(data->context = ft_calloc(1, sizeof(t_ms_context)));
	if (data->context == NULL)
		return (ft_printfd(2, LANG_MALLOC_ERROR, "Parsing/Context"));
	return (EXIT_SUCCESS);
}

int	prompt_handler(t_ms_data *data)
{
	//int	count[4];

	parsing_init(data);
	ft_alist_add_front(data->tokkens = ft_lstnew(ft_strdup_lst(data->prompt)));

	if (!ft_strncmp(data->prompt, "exit", 4))
		ms_exit(data->prompt + 5, data);
	else if (!ft_strncmp(data->prompt, "pwd", 3))
		ms_pwd();
	else if (!ft_strncmp(data->prompt, "env", 3))
		ms_env(data->env_var);
	else if (!ft_strncmp(data->prompt, "echo -n", 8))
		ms_echo(data->prompt + 7, TRUE);
	else if (!ft_strncmp(data->prompt, "echo", 4))
		ms_echo(data->prompt + 5, FALSE);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
