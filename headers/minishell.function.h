/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.function.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:46:42 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/21 12:33:06 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FUNCTION_H
# define MINISHELL_FUNCTION_H
# include "minishell.define.h"
# include "minishell.lang.h"

t_ms_data	*minishell_data_init(t_ms_data *data, char **envp);
int			minishell_main_loop(t_ms_data *data);

#endif
