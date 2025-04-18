/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:32:43 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/18 15:50:00 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

char	*ms_prefix(t_ms_data *data)
{
	const char *custom = get_env_var(data, "ms_prefix");

	if (data->prompt == NULL)
		return (data->prefix);
	if (custom != NULL)
		data->prefix = get_env_var(data, "ms_prefix") + 10;
	else
		data->prefix = LANG_PREFIX;
	if (get_env_lst(data, "ms_rgb") != NULL)
		data->easter_rgb = true;
	else
		data->easter_rgb = false;
	if (data->easter_rgb == true)
		return (ms_prefix_rgb_format(data->prefix, data));
	return (data->prefix);
}
