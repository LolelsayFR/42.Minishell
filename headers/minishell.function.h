/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.function.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:46:42 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/05 08:46:08 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FUNCTION_H
# define MINISHELL_FUNCTION_H

/* ************************************************************************** */
/*  All includes                                                              */
/* ************************************************************************** */

# include "minishell.define.h"
# include "minishell.lang.h"
# include <errno.h>
# include <string.h>
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
void		heredoc_sig(int sig);
void		exec_sig(int sig);

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
char		*tokken_cleaner(char *str, int *flag, int type);
void		heredoc_initer(t_ms_data *data, t_ms_tokken	**tokken);
int			var_placer(char **str, t_pars_args *arg, bool qte_ign);
char		*readline_cleaner(t_ms_data *data);
int			tokken_count(t_ms_data *data, t_pars_args *a);

/* ************************************************************************** */
/*  Exec functions                                                            */
/* ************************************************************************** */

int			ms_exec(t_ms_data *data, t_list *tokkens);
int			exec_one(t_ms_data *data, t_list *tokkens);

void		execve_file_closing(t_ex_data *ex_data);
void		close_file_permission(t_ex_data *ex_data);
void		close_cmd_permission(t_ex_data *ex_data);
void		close_cmd_none(t_ex_data *ex_data);
void		close_execve_one(t_one_data *o_data, char **cmd);
void		ambigous(char *str);
void		bad_dir(char *str);
void		no_permission(char *str);
int			error_filing(t_ex_data *ex_data, t_ms_tokken *tokken);

void		find_one_infile(t_one_data *o_data, t_ms_tokken *tokken);
void		find_one_outfile(t_one_data *o_data, t_ms_tokken *tokken);
void		choose_files(int infile, int outfile);
void		unlink_all(void);
void		are_files_good(t_ms_data *data, t_ex_data *ex_data);
int			outfile_access(char *outfile);
int			infile_access(char *infile);
int			find_outfile(int outfile, int *pipe);
int			find_infile(int outfile, int *pipe);
int			infile_open(int outfile, int type, char *file);
int			outfile_open(int outfile, int type, char *file);
int			files_access(t_list *tokkens);
int			find_files(t_one_data *o_data, t_list *tokkens);

t_list		*first_in_id(t_list *tokkens, int id);
char		**tokken_id_join(t_list *tokkens, int id);
char		*add_path(t_ms_data *data, char *cmd);
void		wait_all_pids(t_ex_data *data);
int			find_nb_cmd(t_list *data);
int			find_nb_pipe(t_list *tokkens);
int			*find_previous_pipe(t_ex_data *data, int *pipe);
int			arg_nb(t_list *tokkens, int id);
int			numb_of_no_nl(char **tab);

void		do_echo(t_ms_data *data, t_ms_tokken *tokken);
void		do_unset(t_ms_data *data, t_ms_tokken *tokken);
void		do_export(t_ms_data *data, t_ms_tokken *tokken);
void		do_cd(t_ms_data *data, t_ms_tokken *tokken);
void		do_exit(t_ms_data *data, t_one_data *o_data);

t_ex_data	*exec_init(t_list *tokkens);
t_one_data	*data_init(void);
void		free_ex_data(t_ex_data *data);
void		free_data(t_one_data *data);
void		exec_close(t_ex_data *ex_data, char **tab, int status, int err);
void		exec_end(t_ex_data *data);

int			is_cmd_in_id(t_ms_data *data, int id);

t_list		*find_cmd(t_list *tokkens);
void		free_tab_err(char **tab);

void		check_standard(int i);
int			open_pipe(t_ex_data *ex_data);
int			close_pipe(t_ex_data *ex_data);

/* ************************************************************************** */
/*  Built-In                                                                  */
/* ************************************************************************** */

int			ms_echo(char *str, int arg);
int			ms_cd(t_ms_data *data, char **path);
int			ms_pwd(t_ms_data *data);
int			ms_unset(t_ms_data *data, char **arg);
int			ms_env(t_ms_data *data);
int			ms_exit(t_ms_data *data, char **exit_args);
int			ms_export(t_ms_data *data, char **av);

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
t_env_lst	*get_env_lst(t_ms_data *data, char *name);
bool		ft_is_only_quote_sp(char *str);
char		**args_split(int i, char *str);
int			ms_ft_strncmp(const char *s1, const char *s2, size_t n);
char		*str_unquote(char *str);
char		*pars_injector(char *str, char *temp, t_pars_args *arg);
int			env_export(char *name, char *content, t_env_lst **head);
char		*ft_strjointab(char **tab);
int			ms_strcmp_e(char *s1, const char *s2);
int			ms_unset_ex(t_ms_data *data, char *arg);
int			ft_countwords(char const *s, char c);

#endif
/* ************************************************************************** */
/*  End of file                                                               */
/* ************************************************************************** */
