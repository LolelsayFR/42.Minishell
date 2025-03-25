/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:32:43 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/25 09:06:53 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.function.h"

char	*ms_prefix(t_ms_data *data)
{
	if (data->prompt == NULL)
		return (data->prefix);
	if (data->easter_rgb == FALSE && !strncmp(data->prompt, "rgb\0", 4))
		data->easter_rgb = TRUE;
	else if (data->easter_rgb == TRUE && !strncmp(data->prompt, "rgb\0", 4))
		data->easter_rgb = FALSE;
	if (data->easter_rgb == TRUE)
		return (ms_prefix_rgb_format(data->prompt, data));
	return (data->prefix);
}
