/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ft_strncmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:25:44 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/24 12:18:58 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (s2[0]);
	if (!s2)
		return (s1[0]);
	i = 0;
	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while (str1[i] && str1[i] == str2[i] && i < n - 1)
		i++;
	return (str1[i] - str2[i]);
}

int	ms_strcmp_e(char *s1, const char *s2)
{
	size_t	i;

	if (!s1)
		return (s2[0]);
	if (!s2)
		return (s1[0]);
	i = 0;
	while ((s1[i] && s1[i] != '=') || (s2[i] && s2[i] != '='))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
