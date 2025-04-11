/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:44:21 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/11 09:35:22 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.function.h"

void	ft_strncat(char **dst_ptr, const char *src, int n)
{
	size_t	dst_len;
	size_t	src_len;
	char	*ans;

	dst_len = ft_strlen(*dst_ptr);
	src_len = ft_strlen(src);
	if (src_len > (size_t)n)
		src_len = n;
	ans = ft_calloc(dst_len + src_len + 1, sizeof(char));
	if (ans)
	{
		ft_memcpy(ans, *dst_ptr, dst_len);
		ft_memcpy(ans + dst_len, src, src_len);
		ans[dst_len + src_len] = '\0';
	}
	free(*dst_ptr);
	*dst_ptr = ans;
}
