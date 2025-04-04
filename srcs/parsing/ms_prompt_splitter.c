/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_splitter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:26:54 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/04 19:24:03 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	tokken_count(t_ms_data *data, int quote, int d_quote, int i)
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
		else if (data->prompt[i] == '|' && (quote + d_quote) % 2 == 0)
			count++;
		i++;
	}
	return (count);
}

char	**prompt_splitter(t_ms_data *data, int quote, int d_quote, int i)
{
	char	**result;
	int		id;
	int		j;
	int		k;

	data->context->nb_cmd = tokken_count(data, quote, d_quote, i);
	result = ft_calloc(data->context->nb_cmd + 1, sizeof(char *));
	id = 0;
	i = 0;
	j = 0;
	k = 0;
	while (ft_isspace(data->prompt[i]) && (quote + d_quote) % 2 == 0)
		i++;
	while (data->prompt[i])
	{
		if (data->prompt[i] == '"' && quote % 2 == 0)
			d_quote++;
		else if (data->prompt[i] == '\'' && d_quote % 2 == 0)
			quote++;
		else if (data->prompt[i] == '|' && (quote + d_quote) % 2 == 0)
		{
			ft_strncat(&result[id], data->prompt + k, j);
			j = 0;
			k = i;
			id++;
		}
		j++;
		i++;
	}
	ft_strncat(&result[id], data->prompt + k, j);
	printf("\n%d\n%d\n", data->context->nb_cmd, i);
	i = 0;
	while (result[i] != NULL)
		ft_putendl_fd(result[i++], 1);
	return (result);
}
