/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_ll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:00:48 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/25 13:58:56 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ft_is_ll(char *str)
{
	int	i;

	i = 0;
	if (*str == '-')
		i = 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	if (ft_strlen(str) > ft_strlen("9223372036854775807"))
		return (1);
	if (i == 1 && ft_strncmp(str, "9223372036854775808", 19) == 0)
		return (0);
	if (i == 1 && (unsigned long long)ft_atoll(str)
		> (unsigned long long)(9223372036854775807))
		return (1);
	if (i == 0 && (unsigned long long)ft_atoll(str) > 9223372036854775807)
		return (1);
	return (0);
}
