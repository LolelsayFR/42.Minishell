/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:44:02 by maillet           #+#    #+#             */
/*   Updated: 2025/03/31 15:48:06 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
}
