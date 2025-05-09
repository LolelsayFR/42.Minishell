/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:30:33 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/05 10:58:00 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static bool	parsing_init(t_ms_data *data)
{
	int	i;

	i = 0;
	while (data->prompt[i]
		&& (ft_isspace(data->prompt[i]) || ft_strrchr("<>", data->prompt[i])))
		i++;
	if (!data->prompt[i] || data->prompt[i] == '|')
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
	if (new_tokken->type == H_D)
		heredoc_initer(ms_get_data(), &new_tokken);
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
	t_pars_args	a;

	if (prompt_checker(data, 0, 0, 0) == false || parsing_init(data) == false)
		return (ft_printfd(2, LANG_PARS_ERROR,
				ms_prefix(data), data->prompt), EXIT_FAILURE);
	data->context->nb_tkn = tokken_count(data, &a);
	data->tab_prompt = prompt_split(data);
	tab_to_tokken(data->tab_prompt, data, 0, 0);
	ft_free_strtab(data->tab_prompt);
	if (!tokkens_checker(data->tokkens, data))
		return (ft_printfd(2, LANG_PARS_ERROR,
				ms_prefix(data), data->prompt), EXIT_FAILURE);
	print_all_tokken(data->tokkens);
	return (EXIT_SUCCESS);
}
