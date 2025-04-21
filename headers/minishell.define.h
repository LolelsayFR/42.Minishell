/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:47:04 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/18 15:09:16 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# include "../submodules/42.libft/libft.h"
# include <stdbool.h>

/* ************************************************************************** */
/*  Global debug config                                                       */
/* ************************************************************************** */

//Global Debug mod
# define MS_DEBUG false
//Tokken printer
# define MS_DE_TOKPRINT true
//Split_tab parsing printer
# define MS_DE_PARS_TAB false
//Unset debug print
# define MS_DE_UNSET false

/* ************************************************************************** */
/*  Tokken info                                                               */
/* ************************************************************************** */

//Tokken types
# define INF		1
# define H_D		2
# define CMD		3
# define ARG		4
# define OUTF_A		5
# define OUTF_R		6
# define B_IN		7
# define END		8
//Tokken flag
# define NONE			1
# define EMPTY_QUOTE 	2
# define CTRL_D_HD		3

/* ************************************************************************** */
/*  Typedef of struct                                                         */
/* ************************************************************************** */

//Tokken struct for exec by parsing
typedef struct s_ms_tokken
{
	int		type;
	char	*content;
	int		flag;
	int		id;
}	t_ms_tokken;

//Context struct for exec by parsing
typedef struct s_ms_context
{
	int		heredocs;
	int		nb_cmd;
	int		nb_tkn;
	int		last_fd;
	bool	hd_is_expand;
	bool	hd_ctrl_c;
}	t_ms_context;

//Env struct
typedef struct s_env_lst
{
	char				*var_name;
	char				*var_cont;
	struct s_env_lst	*next;
}	t_env_lst;

//All data stored in s_ms_data.
typedef struct s_ms_data
{
	int				last_return;
	bool			is_inited;
	bool			is_running;
	bool			easter_rgb;
	char			**env_var;
	char			*prefix;
	char			*prompt;
	char			*init_pwd;
	char			*old_pwd;
	t_list			*tokkens;
	t_env_lst		*env_lst;
	t_ms_context	*context;
}	t_ms_data;

//Parsing utils struct
typedef struct s_pars_args
{
	int		i;
	int		len;
	int		tok;
	int		id;
	int		start;
	int		quote;
	int		d_quote;
	int		count;
}	t_pars_args;

#endif
/* ************************************************************************** */
/*  End of file                                                               */
/* ************************************************************************** */
