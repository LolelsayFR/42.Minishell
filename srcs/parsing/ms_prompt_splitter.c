/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_splitter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:26:54 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/22 17:48:46 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	tokken_count(t_ms_data *data, t_pars_args *a)
{
	ft_bzero(a, sizeof(t_pars_args));
	if (ft_strchr("<>", data->prompt[0]) && data->prompt[0] == data->prompt[1])
		a->i = 2;
	while (ft_isspace(data->prompt[a->i]))
		a->i++;
	while (data->prompt[a->i])
	{
		if (data->prompt[a->i] == '"' && a->quote % 2 == 0)
			a->d_quote++;
		else if (data->prompt[a->i] == '\'' && a->d_quote % 2 == 0)
			a->quote++;
		if (ft_strchr("<>| \t", data->prompt[a->i])
			&& a->i >= 1 && (a->quote + a->d_quote) % 2 == 0)
		{
			if (data->prompt[a->i] == data->prompt[a->i + 1])
				a->i++;
			while (ft_isspace(data->prompt[a->i + 1]))
				a->i++;
			a->count++;
		}
		a->i++;
	}
	return (a->count + 1);
}

static void	prompt_cutter(t_ms_data *data, char **result, t_pars_args *a)
{
	if (a->i >= 1 && (a->quote + a->d_quote) % 2 == 0)
	{
		ft_strncat(&result[a->tok], data->prompt + a->start, a->len);
		a->len = 0;
		a->start = a->i;
		a->tok++;
		if (data->prompt[a->i] == data->prompt[a->i + 1])
		{
			a->i++;
			a->len++;
		}
		while (ft_isspace(data->prompt[a->i + 1]))
		{
			a->i++;
			a->len++;
		}
	}
}

static void	prompt_split_jumper(t_ms_data *data, t_pars_args *a)
{
	if (ft_strchr("<>", data->prompt[0]) && data->prompt[0] == data->prompt[1])
		a->i = 2;
	while (ft_isspace(data->prompt[a->i]))
		a->i++;
}

char	**prompt_split(t_ms_data *data)
{
	char		**result;
	t_pars_args	a;

	data->context->nb_tkn = tokken_count(data, &a);
	ft_bzero(&a, sizeof(t_pars_args));
	result = ft_calloc(data->context->nb_tkn + 2, sizeof(char *));
	prompt_split_jumper(data, &a);
	a.len = a.i;
	while (data->prompt[a.i])
	{
		if (((ft_strchr("<>| \t", data->prompt[a.i])
					&& (a.quote + a.d_quote) % 2 == 0))
			|| ft_isspace(data->prompt[a.i]))
			prompt_cutter(data, result, &a);
		else if (data->prompt[a.i] == '"' && a.quote % 2 == 0)
			a.d_quote++;
		else if (data->prompt[a.i] == '\'' && a.d_quote % 2 == 0)
			a.quote++;
		a.len++;
		a.i++;
	}
	ft_strncat(&result[a.tok], data->prompt + a.start, a.len);
	result[data->context->nb_tkn + 1] = NULL;
	return (result);
}

bool	tokkens_checker(t_list *lst, t_ms_data *data)
{
	t_ms_tokken	*tokken;
	t_ms_tokken	*tokken_next;

	tokken = (t_ms_tokken *)lst->content;
	if (tokken->id != 0 || (tokken->content == NULL
			&& tokken->flag != EMPTY_QUOTE))
		return (false);
	while (lst && lst->next)
	{
		tokken = (t_ms_tokken *)lst->content;
		tokken_next = (t_ms_tokken *)lst->next->content;
		if (tokken_next->id - tokken->id > 1 || (tokken->content == NULL
				&& tokken->flag != EMPTY_QUOTE))
			return (false);
		lst = lst->next;
	}
	if (ft_lstsize(data->tokkens) > 1)
		ft_lstremoveone(&data->tokkens,
			ft_lstlast(data->tokkens), tokken_destructor);
	else
	{
		ft_lstclear(&data->tokkens, tokken_destructor);
		data->tokkens = NULL;
	}
	return (true);
}
