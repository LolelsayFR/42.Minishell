/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokken_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:12:58 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/11 23:34:26 by emaillet         ###   ########.fr       */
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
	return (ft_strdup(str));
}

char	*tokken_var_placer(char *str, t_ms_data *data)
{
	char		*result;
	t_env_lst	*var_link;

	var_link = get_env_lst(data, str);
	(void)var_link;
	result = ft_strdup(str);
	return (result);
}

char	*tokken_cleaner(char *str, int *flag)
{
	char	*result;
	char	*trim;

	trim = ft_strtrim(str, "<> ");
	nufree(str);
	if (ft_is_only_quote_sp(trim))
		*flag = EMPTY_QUOTE;
	else
		*flag = NONE;
	result = tokken_unquote(trim);
	nufree(trim);
	return (result);
}
