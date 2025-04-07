/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt_tabtotokken.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:14:41 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/07 10:45:03 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static int	tokken_get_type(char *str)
{
	if (*str == '<' && *str + 1 == '<')
		return (H_D);
	else if (*str == '>' && *str + 1 == '>')
		return (OUTF_A);
	else if (*str == '<')
		return (INF);
	else if (*str == '>')
		return (OUTF_R);
	return (CMD);
}

void	tab_to_tokken(char **tab, t_ms_data *data, int i)
{
	char	*content;
	int		type;
	int		id;

	id = 0;
	while (tab[i] != NULL)
	{
		type = tokken_get_type(tab[i]);
		content = ft_strtrim(tab[i], "<>| \t");
		printf("%s\n", content);
		ft_lstadd_back(&data->tokkens,
			ft_lstnew(tokken_init(content, data, id, type)));
		if (type == CMD)
			id++;
		i++;
	}
}
