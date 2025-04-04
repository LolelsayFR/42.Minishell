/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:06:32 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/04 09:46:09 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_files
{
	int				fd;
	int				file_t;
	struct s_files	*next;
}	t_files;

typedef struct s_pids
{
	pid_t			pid;
	struct s_pids	*next;
}	t_pids;

t_files	*open_all(t_list *tokkens);
void	files_clear(t_files *files);
t_files	*new_files(void);

#endif
