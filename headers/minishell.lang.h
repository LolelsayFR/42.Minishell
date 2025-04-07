/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.lang.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:47:01 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/07 11:01:26 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LANG_H
# define MINISHELL_LANG_H

/* ************************************************************************** */
/*  Error and warn messages                                                   */
/* ************************************************************************** */
# define LANG_EXIT_ERROR "%sexit: -: numeric argument required\n"
# define LANG_PARS_ERROR "%sParsing error : %s\n"
# define LANG_MALLOC_ERROR "%sMalloc error : %s\n"
# define LMEPC "Parsing/Context"
# define COUNT_WRONG " : too many arguments\n"
# define NUMERIC_ERROR "numeric argument required\n"
# define DIR_ERROR "No such file or directory\n"
# define DIR_COUNT "too many arguments\n"

/* ************************************************************************** */
/*  Other language constant                                                   */
/* ************************************************************************** */
# define LANG_PREFIX "MINI MISHELL : "

#endif
/* ************************************************************************** */
/*  End of file                                                               */
/* ************************************************************************** */
