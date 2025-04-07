/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltolen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:00:48 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/07 09:21:42 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ft_is_ll(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	if (ft_strlen(str) > ft_strlen("9223372036854775807"))
		return (1);
	if (ft_strncmp("9223372036854775808", str, ft_strlen(str)) == 0)
		return (0);
	if (ft_atol(str) <= 0)
		return (1);
	return (0);
}
