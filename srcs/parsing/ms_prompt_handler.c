/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:30:33 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/03 15:38:56 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	parsing_init(t_ms_data *data)
{
	if (data->context != NULL)
		nufree(data->context);
	if (data->tokkens != NULL)
		(ft_lstclear(&data->tokkens, nufree), data->context = NULL);
	ft_alist_add_front(data->context = ft_calloc(1, sizeof(t_ms_context)));
	if (data->context == NULL)
		return (ft_printfd(2, LANG_MALLOC_ERROR, ms_prefix(data), LMEPC));
	return (EXIT_SUCCESS);
}

// static t_ms_tokken	*tokken_creator(char *content, t_ms_data *data)
// {
// 	t_ms_tokken	*new;

// 	ft_alist_add_front(new = ft_calloc(1, sizeof(t_ms_tokken)));
// 	if (new == NULL)
// 		return (ft_printfd(2, LANG_MALLOC_ERROR, ms_prefix(data), "Tokken"));
// 	return (new);
// }


int	prompt_handler(t_ms_data *data)
{
	int		count[4];
	char	**splited_prompt;

	parsing_init(data);
	((void)count);
	splited_prompt = ft_split_spacer(data->prompt);
	if (splited_prompt == NULL)
		return (ft_printfd(2, LANG_MALLOC_ERROR, ms_prefix(data), "Split"));
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
