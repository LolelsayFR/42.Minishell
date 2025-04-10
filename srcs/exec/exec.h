/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:06:32 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/10 10:37:17 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.function.h"

typedef struct s_files
{
	int				fd;
	int				file_t;
	struct s_files	*next;
}	t_files;

typedef struct s_ex_data
{
	t_files	*files;
	int		*pid;
	int		nb_cmd;
}	t_ex_data;

int		outfile_open(int outfile, int type, char *file);
int		infile_open(int outfile, int type, char *file);
int		infile_access(char *infile);
int		outfile_access(char *outfile);

int		find_nb_cmd(t_list *data);

void	wait_all_pids(t_ex_data *data);

int		files_access(t_list *tokkens);
void	files_clear(t_files *files);

t_files	*new_files(void);

char	*add_path(char *cmd, char **env);

void	free_ex_data(t_ex_data *data);

void	print_files(t_files *files);
void	print_pids(t_ex_data *data);

#endif
