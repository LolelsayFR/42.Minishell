/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.function.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:46:42 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/07 10:46:22 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FUNCTION_H
# define MINISHELL_FUNCTION_H

/* ************************************************************************** */
/*  All includes                                                              */
/* ************************************************************************** */

# include "minishell.define.h"
# include "minishell.lang.h"
# include <stdint.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "../submodules/42.libft/libft.h"

/* ************************************************************************** */
/*  Minishell main functions                                                  */
/* ************************************************************************** */

t_ms_data	*minishell_data_init(t_ms_data *data, char **envp);
int			minishell_main_loop(t_ms_data *data);
t_ms_data	*ms_get_data(void);
void		ms_close(unsigned char exit_value, t_ms_data *data);

/* ************************************************************************** */
/*  Minishel signals functions                                                */
/* ************************************************************************** */

t_bool		ms_sig_init(t_ms_data *data);

/* ************************************************************************** */
/*  Minishell Prefix functions                                                */
/* ************************************************************************** */

char		*ms_prefix_rgb_format(char *prompt, t_ms_data *data);
char		*ms_prefix(t_ms_data *data);

/* ************************************************************************** */
/*  Parsing functions                                                         */
/* ************************************************************************** */

int			prompt_handler(t_ms_data *data);
void		tokken_destructor(void *tokken);
t_ms_tokken	*tokken_init(char *content, t_ms_data *data, int id, int type);
char		**prompt_split(t_ms_data *data, int i[6]);
int			tokken_count(t_ms_data *data, int quote, int d_quote, int i);
void        tab_to_tokken(char **tab, t_ms_data *data, int i);

/* ************************************************************************** */
/*  Exec functions                                                            */
/* ************************************************************************** */

int			ms_exec(t_list *tokkens, t_ms_data *data);

/* ************************************************************************** */
/*  Built-In : Echo functions                                                 */
/* ************************************************************************** */

int			ms_echo(char *str, t_bool option);

/* ************************************************************************** */
/*  Built-In : Cd functions                                                   */
/* ************************************************************************** */

/* ************************************************************************** */
/*  Built-In : Pwd functions                                                  */
/* ************************************************************************** */

int			ms_pwd(void);

/* ************************************************************************** */
/*  Built-In : Export functions                                               */
/* ************************************************************************** */

/* ************************************************************************** */
/*  Built-In : Unset functions                                                */
/* ************************************************************************** */

/* ************************************************************************** */
/*  Built-In : Env functions                                                  */
/* ************************************************************************** */

int			ms_env(char **envp);

/* ************************************************************************** */
/*  Built-In : Exit functions                                                 */
/* ************************************************************************** */

int			ms_exit(char *exit_status, t_ms_data *data);

/* ************************************************************************** */
/*  Other/Utils functions                                                     */
/* ************************************************************************** */

char		**ft_split_spacer(char const *s);
void		ft_strncat(char **dst_ptr, const char *src, int n);
int	        *ft_int_aray(int init_value, int size);
int			ft_tabstr_len(char **tab);
int			ft_str_is_num(char *str);

#endif
/* ************************************************************************** */
/*  End of file                                                               */
/* ************************************************************************** */
