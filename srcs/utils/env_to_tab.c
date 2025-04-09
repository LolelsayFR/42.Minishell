/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:20:18 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/09 15:35:18 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	env_len(t_env_lst *env)
{
	int			i;
	t_env_lst	*temp;

	i = 0;
	temp = env;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

char	**env_to_tab(t_env_lst *env)
{
	t_env_lst	*temp;
	char		**tab;
	int			y;
	int			i;

	i = 0;
	y = env_len(env);
	tab = malloc(y * sizeof(char *));
	while (i < y)
	{
		tab[i] = ft_strjoin(temp->var_name, temp->var_cont);
		temp = temp->next;
		i++;
	}
	return (tab);
}
