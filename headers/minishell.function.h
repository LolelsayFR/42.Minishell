/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.function.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:46:42 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/11 18:32:43 by artgirar         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
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

bool		ms_sig_init(t_ms_data *data);

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
t_ms_tokken	*tokken_init(char *content, int id, int type, int f);
char		**prompt_split(t_ms_data *data);
void		tab_to_tokken(char **tab, t_ms_data *data, int i, int save_id);
bool		tokkens_checker(t_list *lst, t_ms_data *data);

/* ************************************************************************** */
/*  Exec functions                                                            */
/* ************************************************************************** */

int			ms_exec(t_ms_data *data, t_list *tokkens);

/* ************************************************************************** */
/*  Built-In                                                                  */
/* ************************************************************************** */

int			ms_echo(t_ms_data *data, char *str);
int			ms_cd(t_ms_data *data, char *path);
int			ms_pwd(t_ms_data *data);
int			ms_unset(t_ms_data *data, char *arg);
int			ms_env(t_ms_data *data);
int			ms_exit(t_ms_data *datachar, char *exit_status);

/* ************************************************************************** */
/*  Other/Utils functions                                                     */
/* ************************************************************************** */

char		**ft_split_spacer(char const *s);
void		ft_strncat(char **dst_ptr, const char *src, int n);
int			ft_tabstr_len(char **tab);
int			ft_str_is_num(char *str);
long long	ft_atoll(const char *nptr);
int			ft_is_ll(char *str);
char		*get_env(t_ms_data *data, char *var);
void		print_all_tokken(t_list *lst_head);
char		*get_env_var(t_ms_data *data, char *var);
t_env_lst	*env_to_lst(char **env);
void		free_env(t_env_lst *env);
char		**env_to_tab(t_env_lst *env);
void		print_tab(char **tab);
void		double_close(int fd1, int fd2);
bool		ft_str_is_space(char *str);
bool		is_builtin(char *str);

#endif
/* ************************************************************************** */
/*  End of file                                                               */
/* ************************************************************************** */
