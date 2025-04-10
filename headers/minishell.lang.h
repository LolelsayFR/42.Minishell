/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.lang.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:47:01 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/10 18:29:01 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LANG_H
# define MINISHELL_LANG_H

/* ************************************************************************** */
/*  Error and warn messages                                                   */
/* ************************************************************************** */
# define LANG_PARS_ERROR "%sParsing error : %s\n"
# define LANG_MALLOC_ERROR "%sMalloc error : %s\n"
# define EXIT_COUNT_WRONG "%sexit: too many arguments\n"
# define EXIT_NUM_ERROR "%sexit: %s : numeric argument required\n"
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
