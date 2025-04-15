/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokken_printer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:26:23 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/15 10:40:17 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

static void	print_tokken(t_ms_tokken *tokken)
{
	printf(GRN"\nTokken id = %d", tokken->id);
	printf(YEL"\nType id : %d"RES, tokken->type);
	if (tokken->type == INF)
		printf("Type : INFILE");
	else if (tokken->type == H_D)
		printf("Type : HEREDOC");
	else if (tokken->type == CMD)
		printf("Type : COMMAND");
	else if (tokken->type == ARG)
		printf("Type : ARGUMENT");
	else if (tokken->type == B_IN)
		printf("Type : BUILT-IN");
	else if (tokken->type == OUTF_A)
		printf("Type : OUTFILE APPEND");
	else if (tokken->type == OUTF_R)
		printf("Type : OURFILE REPLACE");
	else if (tokken->type == END)
		printf("Type : END");
	if (tokken->flag == NONE)
		printf("\nFlag : None");
	else if (tokken->flag == EMPTY_QUOTE)
		printf("\nFlag : Only quote");
	else if (tokken->flag == CTRL_D_HD)
		printf("\nFlag : Ctrl-D Heredoc");
	printf(YEL"\nContent = %s\n"RES, tokken->content);
}

void	print_all_tokken(t_list *lst_head)
{
	t_ms_tokken	*tokken;
	t_list		*lst;
	int			i;

	if (MS_DEBUG == false || MS_DE_TOKPRINT == false)
		return ;
	printf(RED"\n"
		"/* ****************************************************** */\n"
		"/*  List of tokkens was send to exec                      */\n"
		"/* ****************************************************** */"RES);
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
