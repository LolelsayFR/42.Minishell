/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_unquote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:02:26 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/16 10:59:10 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static char	*injector(char *str, char *temp, t_pars_args *arg)
{
	char	*join;

	temp = ft_substr(str, arg->i + 1, ft_strlen(str) - arg->i);
	str[arg->i] = '\0';
	join = ft_strjoin(str, temp);
	free(temp);
	free(str);
	return (join);
}

char	*str_unquote(char *str)
{
	t_pars_args	arg;

	ft_bzero(&arg, sizeof(t_pars_args));
	while (str[arg.i])
	{
		if (str[arg.i] == '"' && arg.quote % 2 == 0)
		{
			str = injector(str, NULL, &arg);
			arg.d_quote++;
			continue ;
		}
		else if (str[arg.i] == '\'' && arg.d_quote % 2 == 0)
		{
			str = injector(str, NULL, &arg);
			arg.quote++;
			continue ;
		}
		arg.i++;
	}
	return (str[arg.i] = '\0', str);
}
