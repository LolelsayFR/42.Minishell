/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:40:21 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/11 09:40:37 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

bool	is_builtin(char *str)
{
	if (!ft_strncmp(str, "exit\0", 5))
		return (true);
	if (!ft_strncmp(str, "pwd\0", 4))
		return (true);
	if (!ft_strncmp(str, "env\0", 4))
		return (true);
	if (!ft_strncmp(str, "echo\0", 5))
		return (true);
	if (!ft_strncmp(str, "unset\0", 6))
		return (true);
	if (!ft_strncmp(str, "export\0", 7))
		return (true);
	if (!ft_strncmp(str, "cd\0", 3))
		return (true);
	return (false);
}