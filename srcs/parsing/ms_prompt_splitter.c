/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_splitter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:26:54 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/07 20:33:46 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	tokken_count(t_ms_data *data, int quote, int d_quote, int i)
{
	int		count;

	count = 1;
	while (data->prompt[i])
	{
		while (ft_isspace(data->prompt[i]) && (d_quote + quote) % 2 == 0)
			i++;
		if (data->prompt[i] == '"' && quote % 2 == 0)
			d_quote++;
		else if (data->prompt[i] == '\'' && d_quote % 2 == 0)
			quote++;
		else if ((ft_strchr("|<>", data->prompt[i])
				&& (i == 0 || !ft_strchr("<>|", data->prompt[i - 1])
					|| (i > 0 && ft_isspace(data->prompt[i - 1]))))
			&& (quote + d_quote) % 2 == 0)
			count++;
		i++;
	}
	return (count);
}

static void	prompt_split_loop(t_ms_data *data, char **result, t_pars_args *a)
{
	while (data->prompt[a->i])
	{
		if (data->prompt[a->i] == '"' && a->quote % 2 == 0)
			a->d_quote++;
		else if (data->prompt[a->i] == '\'' && a->d_quote % 2 == 0)
			a->quote++;
		else if ((ft_strchr("|<>", data->prompt[a->i])
				&& (a->i == 0 || !ft_strchr("|<>", data->prompt[a->i - 1])
					|| (a->i > 0 && ft_isspace(data->prompt[a->i - 1]))))
			&& (a->quote + a->d_quote) % 2 == 0)
		{
			ft_strncat(&result[a->k], data->prompt + a->start, a->j);
			a->j = 0;
			a->start = a->i;
			a->k++;
		}
		a->j++;
		a->i++;
	}
}

char	**prompt_split(t_ms_data *data)
{
	char		**result;
	t_pars_args	a;

	ft_bzero(&a, sizeof(t_pars_args));
	data->context->nb_cmd = tokken_count(data, 0, 0, 0);
	result = ft_calloc(data->context->nb_cmd + 2, sizeof(char *));
	prompt_split_loop(data, result, &a);
	ft_strncat(&result[a.k], data->prompt + a.start, a.j);
	result[data->context->nb_cmd + 1] = NULL;
	return (result);
}

