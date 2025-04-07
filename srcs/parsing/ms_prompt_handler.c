/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:30:33 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/06 03:53:35 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	parsing_init(t_ms_data *data)
{
	ft_bzero(data->context, sizeof(t_ms_context));
	if (data->tokkens != NULL)
		(ft_lstclear(&data->tokkens, tokken_destructor), data->context = NULL);
	if (data->context == NULL)
		return (ft_printfd(2, LANG_MALLOC_ERROR, ms_prefix(data), LMEPC));
	return (EXIT_SUCCESS);
}

void	*tokken_init(char *content, t_ms_data *data, int id)
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
	new_tokken->id = id;
	ft_lstadd_back(&data->tokkens, new);
	return (new_tokken);
}

void	tokken_destructor(void *tokken)
{
	t_ms_tokken	*this;

	this = tokken;
	if (this->content != NULL)
		nufree(this->content);
	nufree(tokken);
}

static int	prompt_checker(t_ms_data *data, int quote, int d_quote, int i)
{
	while (data->prompt[i])
	{
		if (data->prompt[i] == '"' && quote % 2 == 0)
			d_quote++;
		else if (data->prompt[i] == *("'") && d_quote % 2 == 0)
			quote++;
		else if (((data->prompt[i] == '|' && data->prompt[i + 1] == '|')
				|| ft_strchr("&*;\\", data->prompt[i])
				|| (data->prompt[i] == '<' && data->prompt[i + 1] == '<'
					&& data->prompt[i + 2] == '<')
				|| (data->prompt[i] == '>' && data->prompt[i + 1] == '>'
					&& data->prompt[i + 2] == '>')
				|| (data->prompt[i] == '>' && data->prompt[i + 1] == '<')
				|| (data->prompt[i] == '<' && data->prompt[i + 1] == '>')
			) && (quote + d_quote) % 2 == 0)
			return (EXIT_FAILURE);
		i++;
	}
	if (quote % 2 != 0 || d_quote % 2 != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	prompt_handler(t_ms_data *data)
{
	int		count[4];
	char	**split_prompt;
	int		i;

	((void)count, (void)i);
	i = 0;
	if (prompt_checker(data, 0, 0, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	parsing_init(data);
	split_prompt = prompt_split(data, ft_int_aray(0, 6));
	ft_free_strtab(split_prompt);
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
