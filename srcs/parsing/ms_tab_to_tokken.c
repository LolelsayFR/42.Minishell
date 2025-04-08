/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tab_to_tokken.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:14:41 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/08 17:00:06 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	tokken_get_type(char *str, bool is_first)
{
	if (str[0] == '<' && str[1] == '<')
		return (H_D);
	else if (str[0] == '>' && str[1] == '>')
		return (OUTF_A);
	else if (str[0] == '<')
		return (INF);
	else if (str[0] == '>')
		return (OUTF_R);
	else if (str[0] == '|' || is_first)
		return (CMD);
	return (ARG);
}

void	tab_to_tokken(char **tab, t_ms_data *data, int i)
{
	char	*content;
	int		type;
	int		id;

	id = 0;
	while (tab[i] != NULL)
	{
		if (i == 0)
			type = tokken_get_type(tab[i], true);
		else
			type = tokken_get_type(tab[i], false);
		if (type == CMD)
			id++;
		content = ft_strtrim(tab[i], " \t");
		if (ft_strlen(content) < 1)
		{
			free(content);
			i++;
			continue ;
		}
		ft_lstadd_back(&data->tokkens,
			ft_lstnew(tokken_init(ft_strtrim(content, "<>|"), data, id, type)));
		free(content);
		i++;
	}
}
