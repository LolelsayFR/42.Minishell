/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.lang.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:47:01 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/16 15:16:11 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LANG_H
# define MINISHELL_LANG_H

/* ************************************************************************** */
/*  Error and warn messages                                                   */
/* ************************************************************************** */

# define LANG_PARS_ERROR "%sPrompt error : %s\n"
# define LANG_MALLOC_ERROR "%sMalloc error : %s\n"
# define EXIT_NUM_ERROR "%sexit: %s : numeric argument required\n"
# define EXIT_COUNT_WRONG "%sexit: too many arguments\n"
# define HDW "%swarning: here-doc not delimited by end-of-file (wanted `%s')\n"
# define DIR_ERROR "%scd: %s: No such file or directory\n"
# define DIR_COUNT "%scd: too many arguments\n"
# define ECHO_NO_SPACE "%s write error: no space left to write\n"

/* ************************************************************************** */
/*  Other language constant                                                   */
/* ************************************************************************** */
# define LANG_PREFIX "MINI MISHELL : "

#endif
/* ************************************************************************** */
/*  End of file                                                               */
/* ************************************************************************** */
