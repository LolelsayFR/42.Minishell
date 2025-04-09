/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:47:04 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/09 14:49:53 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# include "../submodules/42.libft/libft.h"
# include <stdbool.h>

/* ************************************************************************** */
/*  Return value                                                              */
/* ************************************************************************** */
# define EXIT_SUCCESS 0
# define EXIT_ERROR 1

/* ************************************************************************** */
/*  Tokken type                                                               */
/* ************************************************************************** */

# define INF 0
# define H_D 1
# define CMD 2
# define ARG	3
# define OUTF_A 4
# define OUTF_R 5
# define B_IN	6

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
	int	heredocs;
	int	nb_cmd;
	int	nb_tkn;
}	t_ms_context;

//All data stored in s_ms_data.
typedef struct s_ms_data
{
	bool			is_inited;
	bool			is_running;
	bool			easter_rgb;
	char			**env_var;
	char			*prefix;
	char			*prompt;
	int				last_return;
	t_ms_context	*context;
	t_list			*tokkens;
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
