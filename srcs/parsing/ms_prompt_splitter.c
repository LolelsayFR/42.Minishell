/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_splitter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:26:54 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/04 16:51:29 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	tokken_count(t_ms_data *data, int quote, int d_quote, int i)
{
	int	count;

	while (data->prompt[i])
	{
		while (data->prompt[i] != '"' && d_quote % 2 == 1)
			i++;
		while (data->prompt[i] != *("'") && quote % 2 == 1)
			i++;
		if (data->prompt[i] == '"' && quote % 2 == 0)
			d_quote++;
		else if (data->prompt[i] == *("'") && d_quote % 2 == 0)
			quote++;
		else if (data->prompt[i] == '|' && (quote + d_quote) % 2 == 1)
			count++;
		i++;
	}
	return (EXIT_SUCCESS);
}

char	**prompt_splitter(t_ms_data *data, int quote, int d_quote, int i)
{
	char	**result;

	data->context->nb_cmd = tokken_count(data, quote, d_quote, i);
	result = ft_calloc(data->context->nb_cmd, sizeof(char));
	printf("\n%d\n\n", data->context->nb_cmd);
	return (result);
}
