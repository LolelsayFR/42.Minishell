/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/08 15:02:38 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

char	*write_all_args(t_ms_data *data)
{
	char		*all_str;
	t_list		*tokkens;
	t_ms_tokken	*temp;
	int			i;

	tokkens = data->tokkens;
	all_str = NULL;
	i = 0;
	while (tokkens != NULL)
	{
		temp = tokkens->content;
		if (temp->type == ARG)
		{
			if (i == 0)
				i = 1;
			else
				ft_strcat(&all_str, " ");
			ft_strcat(&all_str, temp->content);
		}
		tokkens = tokkens->next;
	}
	return (all_str);
}

int	ms_echo(t_ms_data *data, t_list *tokkens)
{
	int			i;
	int			fd;
	t_ms_tokken	*temp;
	char		*save;

	i = 5;
	fd = -1;
	save = NULL;
	while (tokkens != NULL)
	{
		temp = tokkens->content;
		if ((temp->type == OUTF_A || temp->type == OUTF_R))
		{
			if (fd != -1)
				close(fd);
			fd = open(temp->content, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		tokkens = tokkens->next;
	}
	save = write_all_args(data);
	if (fd == -1)
		fd = 1;
	while (save[i] != '\0')
		write(fd, &save[i++], 1);
	return (free(save), data->last_return = 0, 0);
}
