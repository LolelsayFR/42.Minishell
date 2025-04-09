/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:30:33 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/09 09:08:31 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	parsing_init(t_ms_data *data)
{
	ft_bzero(data->context, sizeof(t_ms_context));
	if (data->tokkens != NULL)
		(ft_lstclear(&data->tokkens, tokken_destructor), data->tokkens = NULL);
	return (EXIT_SUCCESS);
}

t_ms_tokken	*tokken_init(char *content, t_ms_data *data, int id, int type)
{
	t_ms_tokken	*new_tokken;

	new_tokken = ft_calloc(1, sizeof(t_ms_tokken));
	if (new_tokken == NULL)
		return (ft_printfd(2, LANG_MALLOC_ERROR,
				ms_prefix(data), "Tokken/Struct"), NULL);
	new_tokken->content = content;
	new_tokken->id = id;
	new_tokken->type = type;
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
		else if (data->prompt[i] == '\'' && d_quote % 2 == 0)
			quote++;
		else if (((data->prompt[i] == '|' && data->prompt[i + 1] == '|')
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
	char	**tab_prompt;
	int		i;

	((void)count, (void)i);
	i = 0;
	if (prompt_checker(data, 0, 0, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	parsing_init(data);
	tab_prompt = prompt_split(data);
	tab_to_tokken(tab_prompt, data, 0);
	ft_free_strtab(tab_prompt);
	if (!ft_strncmp(data->prompt, "exit", 4))
		ms_exit(data->prompt, data);
	else if (!ft_strncmp(data->prompt, "pwd", 3))
		ms_pwd(data);
	else if (!ft_strncmp(data->prompt, "env", 3))
		ms_env(data);
	else if (!ft_strncmp(data->prompt, "echo", 4))
		ms_echo(data, data->prompt, 1);
	else if (!ft_strncmp(data->prompt, "cd", 2))
		ms_cd(data, data->prompt);
	print_all_tokken(data->tokkens);
	return (EXIT_SUCCESS);
}
