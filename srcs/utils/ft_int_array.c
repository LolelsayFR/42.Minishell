/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 01:32:32 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/06 03:54:39 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

int	*ft_int_aray(int init_value, int size)
{
	int	*result;
	int	i;

	i = 0;
	ft_alist_add_back(result = ft_calloc(size + 1, sizeof(int)));
	while (i <= size)
		result[i++] = init_value;
	return (result);
}
