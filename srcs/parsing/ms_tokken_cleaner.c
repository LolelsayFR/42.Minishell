/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokken_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:12:58 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/11 10:17:55 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static char	*tokken_unquote(char *str)
{
	t_pars_args	arg;
	char		*temp;

	ft_bzero(&arg, sizeof(t_pars_args));
	while (str[arg.i])
	{
		if (str[arg.i] == '"' && arg.quote % 2 == 0)
		{
			temp = ft_substr_lst(str, arg.i + 1, ft_strlen(str) - arg.i);
			str[arg.i] = '\0';
			str = ft_strjoin_lst(str, temp);
			arg.d_quote++;
			continue ;
		}
		else if (str[arg.i] == '\'' && arg.d_quote % 2 == 0)
		{
			temp = ft_substr_lst(str, arg.i + 1, ft_strlen(str) - arg.i);
			str[arg.i] = '\0';
			str = ft_strjoin_lst(str, temp);
			arg.quote++;
			continue ;
		}
		arg.i++;
	}
	return (str[arg.i] = '\0', ft_strdup(str));
}

static char	*tokken_var_placer(char *str, t_ms_data *data)
{
	char	*result;

	result = ft_strdup(str);
	return (result);
}

char	*tokken_cleaner(char *str, int *flag)
{
	char	*result;
	char	*trim;
	char	*var_placed;

	trim = ft_strtrim(str, "<> ");
	nufree(str);
	var_placed = tokken_var_placer(trim, ms_get_data());
	nufree(trim);
	if (!ft_strcmp(var_placed, "\"\"") || !ft_strcmp(var_placed, "''"))
		*flag = EMPTY_QUOTE;
	else
		*flag = NONE;
	result = tokken_unquote(var_placed);
	if (result[0] == '\0')
		nufree(result);
	nufree(var_placed);
	return (result);
}
