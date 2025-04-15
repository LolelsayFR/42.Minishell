/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:32:43 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/15 15:45:27 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

char	*ms_prefix(t_ms_data *data)
{
	if (data->prompt == NULL)
		return (data->prefix);
	if (data->easter_rgb == false
		&& !strncmp(data->prompt, "test super rgb like jeb_", 20))
		data->easter_rgb = true;
	else if (data->easter_rgb == true
		&& !strncmp(data->prompt, "test super rgb like jeb_", 20))
		data->easter_rgb = false;
	if (data->easter_rgb == true)
		return (ms_prefix_rgb_format(data->prompt, data));
	return (data->prefix);
}
