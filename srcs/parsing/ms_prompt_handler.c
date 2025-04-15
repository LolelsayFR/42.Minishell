/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:30:33 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/15 19:26:53 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static bool	parsing_init(t_ms_data *data)
{
	int	i;

	i = 0;
	while (ft_isspace(data->prompt[i]) || ft_strrchr("<>", data->prompt[i]))
		i++;
	if (data->prompt[i] == '|')
		return (false);
	while (data->prompt[i])
		i++;
	i--;
	while (ft_isspace(data->prompt[i]) || ft_strrchr("<>", data->prompt[i]))
		i--;
	if (data->prompt[i] == '|')
		return (false);
	ft_bzero(data->context, sizeof(t_ms_context));
	if (data->tokkens != NULL)
		(ft_lstclear(&data->tokkens, tokken_destructor), data->tokkens = NULL);
	return (true);
}

t_ms_tokken	*tokken_init(char *content, int id, int type, int f)
{
	t_ms_tokken	*new_tokken;

	new_tokken = ft_calloc(1, sizeof(t_ms_tokken));
	if (new_tokken == NULL)
		return (ft_printfd(2, LANG_MALLOC_ERROR,
				ms_prefix(ms_get_data()), "Tokken/Struct"), NULL);
	new_tokken->content = content;
	new_tokken->id = id;
	new_tokken->type = type;
	new_tokken->flag = f;
	return (new_tokken);
}

void	tokken_destructor(void *tokken)
{
	t_ms_tokken	*this;

	this = tokken;
	if (this->content != NULL && this->flag != END)
		nufree(this->content);
	nufree(tokken);
}

static bool	prompt_checker(t_ms_data *data, int quote, int d_quote, int i)
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
				|| (data->prompt[i] == '>'
					&& ft_strchr("<|\0", data->prompt[i + 1]))
				|| (data->prompt[i] == '<'
					&& ft_strchr(">|\0", data->prompt[i + 1]))
			) && (quote + d_quote) % 2 == 0)
			return (false);
		i++;
	}
	if (quote % 2 != 0 || d_quote % 2 != 0)
		return (false);
	return (true);
}

int	prompt_handler(t_ms_data *data)
{
	char	**tab_prompt;

	if (prompt_checker(data, 0, 0, 0) == false || parsing_init(data) == false)
		return (EXIT_FAILURE);
	tab_prompt = prompt_split(data);
	tab_to_tokken(tab_prompt, data, 0, 0);
	if (!tokkens_checker(data->tokkens, data))
		return (EXIT_FAILURE);
	ft_free_strtab(tab_prompt);
	heredoc_finder(data->tokkens, data);
	if (!ft_strncmp(data->prompt, "exit", 4))
		ms_exit(data, data->prompt);
	else if (!ft_strncmp(data->prompt, "env", 3))
		ms_env(data);
	else if (!ft_strncmp(data->prompt, "unset", 5))
		ms_unset(data, "str");
	else if (!ft_strncmp(data->prompt, "export", 6))
		ms_export(data, tokken_id_join(data->tokkens, 0));
	print_all_tokken(data->tokkens);
	return (EXIT_SUCCESS);
}
