/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:22:20 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/21 18:23:00 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.define.h"


static size_t	sum_of_char(char *str)
{
	size_t	sum;
	int		i;

	i = 0;
	sum = 0;
	while (str[i])
	{
		sum += str[i];
		i++;
	}
	return (sum);
}

static t_rgb	random_rgb(char *prompt)
{
	static int		seed = -1;
	t_rgb			rgb;
	static int		appel = 0;

	seed += (++appel * sum_of_char(prompt) + (uintptr_t)prompt) % 256;
	seed *= (seed + 2025) % 256;
	rgb.r = (seed % 128);
	seed *= (seed + 2025) % 256;
	rgb.g = (seed % 128);
	seed *= (seed + 2025) % 256;
	rgb.b = (seed % 128);
	return (rgb);
}

static char	*prefix_rgb_format(char *prompt)
{
	char	*temp;
	char	*result;
	t_rgb	*rgb;

	rgb = ft_calloc(1, sizeof(t_rgb));
	*rgb = random_rgb(prompt);
	result = ft_strdup("\e[48;2;");
	temp = ft_ltoa(rgb->r % 160);
	ft_strcat(&temp, ";");
	ft_strcat(&result, temp);
	nufree(temp);
	temp = ft_ltoa(rgb->g % 160);
	ft_strcat(&temp, ";");
	ft_strcat(&result, temp);
	nufree(temp);
	temp = ft_ltoa(rgb->b % 160);
	ft_strcat(&temp, ";");
	ft_strcat(&result, temp);
	nufree(temp);
	ft_strcat(&result, "1m MINI MICHEL ⤵ \e[0m\n");
	nufree(rgb);
	return (result);
}


