/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokken_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:12:58 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/17 18:31:58 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static void	env_var_count(char *str, t_pars_args *arg)
{
	arg->count = 0;
	if (str[arg->i + arg->count] == '$' || str[arg->i + arg->count] == '?'
		|| (ft_isdigit(str[arg->i + arg->count])))
		arg->count = 1;
	else
	{
		while (ft_isalnum(str[arg->i + arg->count])
			|| str[arg->i + arg->count] == '_')
			arg->count++;
	}
}

static void	replace_middle(char **middle)
{
	t_env_lst	*var_link;
	char		*result;

	if ((*middle)[0] == '$')
		result = ft_strdup("$");
	else if ((*middle)[0] == '?')
		result = ft_itoa(ms_get_data()->last_return);
	else if (ft_isdigit((*middle)[0]))
		result = NULL;
	else
	{
		var_link = get_env_lst(ms_get_data(), *middle);
		if (var_link == NULL || var_link->var_cont == NULL)
			result = NULL;
		else
			result = ft_strdup(var_link->var_cont);
	}
	free(*middle);
	*middle = result;
}

int	var_placer(char **str, t_pars_args *arg)
{
	char		*begin;
	char		*middle;
	char		*ending;

	if (arg->quote % 2 == 1)
		return (0);
	env_var_count(*str, arg);
	begin = ft_substr(*str, 0, arg->i - 1);
	middle = ft_substr(*str, arg->i, arg->count);
	if (arg->i + arg->count >= (int)ft_strlen(*str))
		ending = NULL;
	else
		ending = ft_substr(*str, arg->i + arg->count, ft_strlen(*str));
	free(*str);
	replace_middle(&middle);
	if (middle != NULL)
		(ft_strcat(&begin, middle));
	(ft_strcat(&begin, ending), free(ending));
	*str = begin;
	arg->len = (int)ft_strlen(middle);
	return (free(middle), arg->len - 2);
}

static char	*tokken_unquote(char **str, t_pars_args arg)
{
	while (*str != NULL && (*str)[arg.i])
	{
		if ((*str)[arg.i] == '"' && arg.quote % 2 == 0)
		{
			(*str) = pars_injector((*str), NULL, &arg);
			arg.d_quote++;
		}
		else if ((*str)[arg.i] == '\'' && arg.d_quote % 2 == 0)
		{
			(*str) = pars_injector((*str), NULL, &arg);
			arg.quote++;
		}
		else if (arg.i > 1 && (*str)[arg.i - 1] == '$' && ((*str)[arg.i] == '?'
				|| (*str)[arg.i] == '_' || (*str)[arg.i] == '$'
				|| ft_isalnum((*str)[arg.i])))
			arg.i += var_placer(str, &arg);
		arg.i++;
	}
	if (*str == NULL)
		return (ft_strdup("\0"));
	return (*str);
}

char	*tokken_cleaner(char *str, int *flag, int type)
{
	char		*trim;
	t_pars_args	arg;
	char		*result;

	ft_bzero(&arg, sizeof(t_pars_args));
	trim = ft_strtrim(str, "<> ");
	free(str);
	if (ft_is_only_quote_sp(trim))
	{
		free(trim);
		trim = NULL;
		*flag = EMPTY_QUOTE;
	}
	else
		*flag = NONE;
	if (type != H_D)
		result = tokken_unquote(&trim, arg);
	return (result);
}
