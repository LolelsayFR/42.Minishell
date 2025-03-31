/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/03/31 17:27:40 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	ms_exit(char *exit_status)
{
	ft_alist_free();
	exit((unsigned char)ft_atoi(exit_status));
	return (0);
}
