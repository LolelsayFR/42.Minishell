/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tab_to_tokken.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:14:41 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/05 10:57:10 by emaillet         ###   ########.fr       */
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

static int	tab_to_tokken_utils(int *save_id, char **str, int *i)
{
	if (save_id != NULL)
		(*save_id)--;
	free(*str);
	*str = NULL;
	(*i)++;
	return (1);
}

void	tab_to_tokken(char **tab, t_ms_data *data, int i, int save_id)
{
	char		*str;
	t_ms_tokken	tok;

	ft_bzero(&tok, sizeof(t_ms_tokken));
	save_id = -1;
	while (tab[i] != NULL)
	{
		if (tab[i][0] == '|')
			tok.id++;
		str = ft_strtrim(tab[i], "| \t");
		if (ft_strlen(str) < 1)
			if (tab_to_tokken_utils(NULL, &str, &i))
				continue ;
		tok.type = tokken_get_type(str, tok.id, &save_id);
		str = tokken_cleaner(str, &tok.flag, tok.type);
		if (((str == NULL || str[0] == '\0') && tok.flag != EMPTY_QUOTE)
			&& (tok.type == CMD || tok.type == ARG))
			if (tab_to_tokken_utils(&save_id, &str, &i))
				continue ;
		ft_lstadd_back(&data->tokkens, ft_lstnew(tokken_init(
					str, tok.id, tok.type, tok.flag)));
		i++;
	}
	ft_lstadd_back(&data->tokkens,
		ft_lstnew(tokken_init(NULL, tok.id++, END, NONE)));
}
