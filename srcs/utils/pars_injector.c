/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_injector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:08:57 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/17 18:26:33 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

char	*pars_injector(char *str, char *temp, t_pars_args *arg)
{
	char	*join;

	temp = ft_substr(str, arg->i + 1, ft_strlen(str) - arg->i);
	str[arg->i] = '\0';
	join = ft_strjoin(str, temp);
	arg->i--;
	free(temp);
	free(str);
	return (join);
}
