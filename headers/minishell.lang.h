/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.lang.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:47:01 by emaillet          #+#    #+#             */
/*   Updated: 2025/04/25 10:50:46 by emaillet         ###   ########.fr       */
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
# define CD_DIR_ERROR "%scd: %s: No such file or directory\n"
# define CD_NOHOME "%scd: HOME not set\n"
# define CD_DIR_COUNT "%scd: too many arguments\n"
# define NO_SPACE "%swrite error: no space left to write\n"
# define EXEC_SIGSEGV "%sSegmentation fault (execve)\n"
# define EXPORT_ERROR "%sexport: `%s': not a valid identifier\n"
# define EXEC_NOFOUND "%s%s: command not found\n"
# define EXEC_NOPERM "%s%s: Permission Denied\n"
# define EXEC_NODIR "%s%s: No such file or directory\n"

/* ************************************************************************** */
/*  Other language constant                                                   */
/* ************************************************************************** */
# define LANG_PREFIX "MINI MISHELL : "

#endif
/* ************************************************************************** */
/*  End of file                                                               */
/* ************************************************************************** */
