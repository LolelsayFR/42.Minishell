/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_splitter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:26:54 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/07 14:00:19 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	tokken_count(t_ms_data *data, int quote, int d_quote, int i)
{
	int	count;

	count = 1;
	while (data->prompt[i])
	{
		while (data->prompt[i] != '"' && d_quote % 2 == 1)
			i++;
		while (data->prompt[i] != '\'' && quote % 2 == 1)
			i++;
		if (data->prompt[i] == '"' && quote % 2 == 0)
			d_quote++;
		else if (data->prompt[i] == '\'' && d_quote % 2 == 0)
			quote++;
		else if (ft_strchr("|<>", data->prompt[i])
			&& (i == 0 || !ft_strchr("<>", data->prompt[i - 1]))
			&& (quote + d_quote) % 2 == 0)
			count++;
		i++;
	}
	return (count);
}

static void	prompt_split_loop(t_ms_data *data, int i[4], char **result)
{
	int quote;
	int	d_quote;

	d_quote = 0;
	quote = 0;
	while (data->prompt[i[0]])
	{
		if (data->prompt[i[0]] == '"' && quote % 2 == 0)
			d_quote++;
		else if (data->prompt[i[0]] == '\'' && d_quote % 2 == 0)
			quote++;
		else if (ft_strchr("|<>", data->prompt[i[0]]) && (i[0] == 0
				|| !ft_strchr("<>", data->prompt[i[0] - 1]))
			&& (quote + d_quote) % 2 == 0)
		{
			ft_strncat(&result[i[2]], data->prompt + i[3], i[1]);
			i[1] = 0;
			i[3] = i[0];
			i[2]++;
		}
		i[1]++;
		i[0]++;
	}
	ft_strncat(&result[i[2]], data->prompt + i[3], i[1]);
}

char	**prompt_split(t_ms_data *data, int i[6])
{
	char	**result;

	data->context->nb_cmd = tokken_count(data, 0, 0, 0);
	result = ft_calloc(data->context->nb_cmd + 1, sizeof(char *));
	while (ft_isspace(data->prompt[i[0]]) && (i[5] + i[4]) % 2 == 0)
		i[0]++;
	prompt_split_loop(data, i, result);
	return (result);
}

