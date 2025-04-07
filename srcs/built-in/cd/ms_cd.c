/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:20:45 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/07 09:59:25 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_cd(t_ms_data *data, char *path)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_strcat(&pwd, path);
	if (chdir(pwd) == -1)
		data->last_return = 2;
	free(pwd);
	data->last_return = 0;
	return (0);
}
