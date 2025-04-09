/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tab_to_tokken.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:14:41 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/09 19:02:28 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static bool	is_builtin(char *str)
{
	if (!ft_strncmp(str, "exit\0", 5))
		return (true);
	if (!ft_strncmp(str, "pwd\0", 4))
		return (true);
	if (!ft_strncmp(str, "env\0", 4))
		return (true);
	if (!ft_strncmp(str, "echo\0", 5))
		return (true);
	if (!ft_strncmp(str, "unset\0", 6))
		return (true);
	if (!ft_strncmp(str, "export\0", 7))
		return (true);
	if (!ft_strncmp(str, "cd\0", 3))
		return (true);
	return (false);
}

static int	tokken_get_type(char *str, int id, int *save_id)
{
	if (str[0] == '<' && str[1] == '<')
		return (H_D);
	if (str[0] == '>' && str[1] == '>')
		return (OUTF_A);
	if (str[0] == '<')
		return (INF);
	if (str[0] == '>')
		return (OUTF_R);
	if (id != *save_id)
	{
		*save_id = id;
		if (is_builtin(str))
			return (B_IN);
		return (CMD);
	}
	return (ARG);
}

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

static char	*tokken_cleaner(char *str)
{
	char	*result;
	char	*trim;
	char	*var_got;

	trim = ft_strtrim(str, "<>");
	nufree(str);
	var_got = ft_strdup(trim);
	nufree(trim);
	result = tokken_unquote(var_got);
	nufree(var_got);
	return (result);
}

void	tab_to_tokken(char **tab, t_ms_data *data, int i)
{
	char	*content;
	int		type;
	int		id;
	int		save_id;

	id = 0;
	save_id = -1;
	while (tab[i] != NULL)
	{
		if (tab[i][0] == '|')
			id++;
		content = ft_strtrim(tab[i], "| \t");
		if (ft_strlen(content) < 1)
		{
			free(content);
			i++;
			continue ;
		}
		content = tokken_cleaner(content);
		type = tokken_get_type(content, id, &save_id);
		ft_lstadd_back(&data->tokkens, ft_lstnew(tokken_init(
					content, data, id, type)));
		i++;
	}
}
