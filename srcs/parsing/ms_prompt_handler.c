/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:30:33 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/04 10:51:40 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	parsing_init(t_ms_data *data)
{
	//if (data->context != NULL)
	//	nufree(data->context);
	if (data->tokkens != NULL)
		(ft_lstclear(&data->tokkens, tokken_destructor), data->context = NULL);
	ft_alist_add_front(data->context = ft_calloc(1, sizeof(t_ms_context)));
	if (data->context == NULL)
		return (ft_printfd(2, LANG_MALLOC_ERROR, ms_prefix(data), LMEPC));
	return (EXIT_SUCCESS);
}

static t_list	*tokken_creator(char *content, t_ms_data *data)
{
	t_ms_tokken	*new_tokken;
	t_list		*new;

	new_tokken = ft_calloc(1, sizeof(t_ms_tokken));
	if (new_tokken == NULL)
		return (ft_printfd(2, LANG_MALLOC_ERROR,
				ms_prefix(data), "Tokken/Struct"), NULL);
	new = ft_calloc(1, sizeof(t_list));
	if (new == NULL)
		return (ft_printfd(2, LANG_MALLOC_ERROR,
				ms_prefix(data), "Tokken/Link"), NULL);
	new->content = new_tokken;
	new_tokken->content = content;
	return (new);
}

void	tokken_destructor(void *tokken)
{
	t_ms_tokken	*this;

	this = tokken;
	if (this->content != NULL)
		nufree(this->content);
	nufree(tokken);
}

int	prompt_handler(t_ms_data *data)
{
	int		count[4];
	char	**split_prompt;
	int		i;

	i = 0;
	parsing_init(data);
	((void)count);
	split_prompt = ft_split_spacer(data->prompt);
	while (split_prompt[i] != NULL)
		ft_lstadd_back(&data->tokkens, tokken_creator(split_prompt[i++], data));
	nufree(split_prompt);
	if (split_prompt == NULL)
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
