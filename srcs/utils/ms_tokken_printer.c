/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokken_printer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:26:23 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/10 13:48:30 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static void	print_tokken(t_ms_tokken *tokken)
{
	printf(GRN"\nTokken id = %d", tokken->id);
	printf(YEL"\nType id : %d"RES, tokken->type);
	if (tokken->type == INF)
		printf("Type : INFILE");
	if (tokken->type == H_D)
		printf("Type : HEREDOC");
	if (tokken->type == CMD)
		printf("Type : COMMAND");
	if (tokken->type == ARG)
		printf("Type : ARGUMENT");
	if (tokken->type == B_IN)
		printf("Type : BUILT-IN");
	if (tokken->type == OUTF_A)
		printf("Type : OUTFILE APPEND");
	if (tokken->type == OUTF_R)
		printf("Type : OURFILE REPLACE");
	if (tokken->type == END)
		printf("Type : END");
	if (tokken->flag ==	NONE)
		printf("\nFlag : None");
	if (tokken->type == EMPTY_QUOTE)
		printf("\nFlag : Only quote");
	printf(YEL"\nContent = %s\n"RES, tokken->content);
}

void	print_all_tokken(t_list *lst_head)
{
	t_ms_tokken	*tokken;
	t_list		*lst;
	int			i;

	printf(RED"\n"
		"/* ****************************************************** */\n"
		"/*  List of tokkens was send to exec                      */\n"
		"/* ****************************************************** */"RES);
	if (MS_DEBUG == false || MS_DE_TOKPRINT == false)
		return ;
	i = 0;
	lst = lst_head;
	while (lst)
	{
		i++;
		tokken = lst->content;
		print_tokken(tokken);
		lst = lst->next;
	}
	printf(RED"Tokken count = %d"RES, i);
	printf(GRN"\n"
		"/* ****************************************************** */\n"
		"/*  end                                                   */\n"
		"/* ****************************************************** */"RES);
}

