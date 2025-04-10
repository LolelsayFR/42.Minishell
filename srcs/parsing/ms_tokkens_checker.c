/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokkens_checker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:39:02 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/10 14:20:50 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

bool	tokkens_checker(t_list *lst, t_ms_data *data)
{
	t_ms_tokken	*tokken;
	t_ms_tokken	*tokken_next;

	tokken = (t_ms_tokken *)lst->content;
	if (tokken->id != 0 || (tokken->content == NULL
			&& tokken->flag != EMPTY_QUOTE))
		return (false);
	while (lst && lst->next)
	{
		tokken = (t_ms_tokken *)lst->content;
		tokken_next = (t_ms_tokken *)lst->next->content;
		if (tokken_next->id - tokken->id > 1 || (tokken->content == NULL
				&& tokken->flag != EMPTY_QUOTE))
			return (false);
		lst = lst->next;
	}
	if (ft_lstsize(data->tokkens) > 1)
		ft_lstremoveone(&data->tokkens,
			ft_lstlast(data->tokkens), tokken_destructor);
	else
	{
		ft_lstclear(&data->tokkens, tokken_destructor);
		data->tokkens = NULL;
	}
	return (true);
}
