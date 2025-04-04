/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:15:00 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/04 18:29:07 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

long long	ft_atoll(const char *nptr)
{
	long long	save;
	int			n;

	n = 1;
	save = 0;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			n = -n;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		save = (save * 10) + *nptr - '0';
		nptr++;
	}
	return (save * n);
}
