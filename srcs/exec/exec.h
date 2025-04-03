/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:06:32 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/03 10:14:58 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_files
{
	int				fd;
	int				outf_t;
	struct s_files	*next;
}	t_files;

typedef struct s_pids
{
	pid_t			pid;
	struct s_pids	next;
}	t_pids;

#endif
