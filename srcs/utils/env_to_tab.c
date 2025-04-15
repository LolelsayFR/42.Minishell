/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:20:18 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/15 18:42:40 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	env_len(t_env_lst *env)
{
	int			i;
	t_env_lst	*temp;

	i = 0;
	temp = env;
	while (temp != NULL)
	{
		if (temp->var_cont == NULL)
		{
			temp = temp->next;
			continue ;
		}
		temp = temp->next;
		i++;
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
	temp = env;
	tab = malloc((y + 1) * sizeof(char *));
	while (temp != NULL)
	{
		if (temp->var_cont == NULL)
		{
			temp = temp->next;
			continue ;
		}
		tab[i] = ft_strjoin(temp->var_name, temp->var_cont);
		temp = temp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
