/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:47:04 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/21 13:42:58 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# include "../submodules/42.libft/libft.h"

# define EXIT_SUCCESS 0
# define EXIT_ERROR 2
# define TRUE 1
# define FALSE 0

typedef int	t_bool;

typedef struct s_ms_data
{
	t_bool	is_inited;
	t_bool	is_running;
	t_list	*prompts;
}	t_ms_data;

#endif
