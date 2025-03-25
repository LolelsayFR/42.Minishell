/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:47:04 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/25 09:02:52 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# include "../submodules/42.libft/libft.h"

# define EXIT_SUCCESS 0
# define EXIT_ERROR 1
# define TRUE 1
# define FALSE 0

typedef int	t_bool;

typedef struct s_ms_data
{
	t_bool	is_inited;
	t_bool	is_running;
	t_bool	easter_rgb;
	char	*prefix;
	char	*prompt;
}	t_ms_data;

#endif
