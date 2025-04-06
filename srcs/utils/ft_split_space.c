/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:52:13 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/04 17:31:54 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static void	ft_freeall(char **result, size_t j)
{
	while (j--)
		nufree(result[j]);
	nufree(result);
}

static size_t	ft_countab(char const *s)
{
	size_t	count;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	count = 0;
	while (s[i])
	{
		while (ft_isspace(s[i]))
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && !ft_isspace(s[i]))
				i++;
		}
	}
	return (count);
}

static char	**ft_splitinject(char const *s, char **result)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (ft_isspace(s[i]))
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] && !ft_isspace(s[i]))
				i++;
			result[j] = ft_substr(s, start, i - start);
			if (!result[j])
				return (ft_freeall(result, j), NULL);
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split_spacer(char const *s)
{
	char	**result;

	result = (char **)ft_calloc((ft_countab(s) + 1), sizeof(char *));
	if (!result)
		return (NULL);
	result = ft_splitinject(s, result);
	return (result);
}
