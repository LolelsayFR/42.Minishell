/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:06:32 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/10 11:57:59 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.function.h"

typedef struct s_ex_data
{
	int		*pid;
	int		nb_cmd;
}	t_ex_data;

int		outfile_open(int outfile, int type, char *file);
int		infile_open(int outfile, int type, char *file);

t_list	*first_in_id(t_list *tokkens, int id);
int		find_nb_cmd(t_list *data);

void	wait_all_pids(t_ex_data *data);

int		files_access(t_list *tokkens);

char	*add_path(t_ms_data *data, char *cmd);

void	free_ex_data(t_ex_data *data);

#endif
