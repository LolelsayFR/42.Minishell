/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_args_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:26:54 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/05 09:39:26 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	tokken_count_as(char *str, t_pars_args *a)
{
	ft_bzero(a, sizeof(t_pars_args));
	if (ft_strchr("<>", str[0]) && str[0] == str[1])
		a->i = 2;
	while (str[a->i])
	{
		if (str[a->i] == '"' && a->quote % 2 == 0)
			a->d_quote++;
		else if (str[a->i] == '\'' && a->d_quote % 2 == 0)
			a->quote++;
		if (ft_strchr("<>| \t", str[a->i])
			&& a->i >= 1 && (a->quote + a->d_quote) % 2 == 0)
		{
			if (str[a->i] == str[a->i + 1])
				a->i++;
			while (ft_isspace(str[a->i + 1]))
				a->i++;
			a->count++;
		}
		a->i++;
	}
	return (a->count + 1);
}

static void	prompt_cutter(char *str, char **result, t_pars_args *a)
{
	if (a->i >= 1 && (a->quote + a->d_quote) % 2 == 0)
	{
		ft_strncat(&result[a->tok], str + a->start, a->len);
		a->len = 0;
		a->start = a->i;
		a->tok++;
		if (str[a->i] == str[a->i + 1])
		{
			a->i++;
			a->len++;
		}
		while (ft_isspace(str[a->i + 1]))
		{
			a->i++;
			a->len++;
		}
	}
}

char	**args_split(int i, char *str)
{
	char		**result;
	t_pars_args	a;

	i = tokken_count_as(str, &a);
	ft_bzero(&a, sizeof(t_pars_args));
	result = ft_calloc(i + 2, sizeof(char *));
	if (ft_strchr("<>", str[0]) && str[0] == str[1])
		a.i = 2;
	a.len = a.i;
	while (str[a.i])
	{
		if (((ft_strchr("<>| \t", str[a.i])
					&& (a.quote + a.d_quote) % 2 == 0))
			|| ft_isspace(str[a.i]))
			prompt_cutter(str, result, &a);
		else if (str[a.i] == '"' && a.quote % 2 == 0)
			a.d_quote++;
		else if (str[a.i] == '\'' && a.d_quote % 2 == 0)
			a.quote++;
		a.len++;
		a.i++;
	}
	ft_strncat(&result[a.tok], str + a.start, a.len);
	result[i + 1] = NULL;
	return (result);
}
