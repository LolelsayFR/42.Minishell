/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tab_to_tokken.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:14:41 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/11 22:14:20 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

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

void	tab_to_tokken(char **tab, t_ms_data *data, int i, int save_id)
{
	char		*content;
	t_ms_tokken	tokken;

	ft_bzero(&tokken, sizeof(t_ms_tokken));
	save_id = -1;
	while (tab[i] != NULL)
	{
		if (tab[i][0] == '|')
			tokken.id++;
		content = ft_strtrim(tab[i], "| \t");
		if (ft_strlen(content) < 1)
		{
			free(content);
			i++;
			continue ;
		}
		tokken.type = tokken_get_type(content, tokken.id, &save_id);
		content = tokken_cleaner(content, &tokken.flag);
		ft_lstadd_back(&data->tokkens, ft_lstnew(tokken_init(
					content, tokken.id, tokken.type, tokken.flag)));
		i++;
	}
	ft_lstadd_back(&data->tokkens,
		ft_lstnew(tokken_init("", tokken.id++, 7, 0)));
}
