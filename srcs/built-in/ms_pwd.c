/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/04/18 16:10:59 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_pwd(t_ms_data *data)
{
	char	*path;
	int		i;

	path = getcwd(NULL, 0);
	i = printf("%s\n", path);
	if (i == -1)
		ft_printfd(2, NO_SPACE, ms_prefix(ms_get_data()));
	free(path);
	data->last_return = 0;
	return (0);
}
