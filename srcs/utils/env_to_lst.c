/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:29:46 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/09 15:34:33 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	free_env(t_env_lst *env)
{
	t_env_lst	*temp;

	while (env != NULL)
	{
		temp = env->next;
		free(env->var_name);
		free(env->var_cont);
		free(env);
		env = temp;
	}
}

char	*find_cont(char *env_l)
{
	int	i;

	i = 0;
	while (env_l[i] != '\0' && env_l[i] != '=')
		i++;
	if (env_l[i] == '\0')
		return (NULL);
	i++;
	return (ft_strdup(&env_l[i]));
}

char	*find_name(char *env_l)
{
	int	i;

	i = 0;
	while (env_l[i] != '\0' && env_l[i] != '=')
		i++;
	return (ft_substr(env_l, 0, i));
}

t_env_lst	*new_env(void)
{
	t_env_lst	*env;

	env = malloc(sizeof(t_env_lst));
	env->var_name = NULL;
	env->var_cont = NULL;
	env->next = NULL;
	return (env);
}

t_env_lst	*env_to_lst(char **env)
{
	int			i;
	t_env_lst	*env_lst;
	t_env_lst	*temp;

	i = 0;
	env_lst = new_env();
	temp = env_lst;
	while (env[i] != NULL)
	{
		env_lst->var_name = find_name(env[i]);
		env_lst->var_cont = find_cont(env[i]);
		i++;
		env_lst->next = new_env();
		env_lst = env_lst->next;
	}
	env_lst = temp;
	return (env_lst);
}
