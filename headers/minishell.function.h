/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.function.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:46:42 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/25 09:05:52 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FUNCTION_H
# define MINISHELL_FUNCTION_H
# include "minishell.define.h"
# include "minishell.lang.h"
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../submodules/42.libft/libft.h"

t_ms_data	*minishell_data_init(t_ms_data *data, char **envp);
int			minishell_main_loop(t_ms_data *data);
char		*ms_prefix_rgb_format(char *prompt, t_ms_data *data);
char		*ms_prefix(t_ms_data *data);

#endif
