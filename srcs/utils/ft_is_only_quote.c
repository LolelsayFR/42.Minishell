/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_only_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:42:22 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/11 22:54:25 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

bool	ft_is_only_quote_sp(char *str)
{
	int i;
	int	quote;
	int	d_quote;

	i = 0;
	quote = 0;
	d_quote = 0;
	while (str[i])
	{
		if (str[i] == '"' && quote % 2 == 0)
			d_quote++;
		else if (str[i] == '\'' && d_quote % 2 == 0)
			quote++;
		else
			return (false);
		i++;
	}
	return (true);
}
