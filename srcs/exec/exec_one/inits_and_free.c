/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:44:03 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/25 10:42:52 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

t_one_data	*data_init(void)
{
	t_one_data	*data;

	data = malloc(sizeof(t_one_data));
	data->inf = 0;
	data->outf = 1;
	return (data);
}

void	free_data(t_one_data *data)
{
	if (data->inf != 0 && data->inf != -1 && data->inf != -2)
		close(data->inf);
	if (data->outf != 1 && data->outf != -1 && data->outf != -2)
		close(data->outf);
	check_standard(3);
	free(data);
}
