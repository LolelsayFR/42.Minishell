/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:06:32 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/07 15:53:35 by artgirar         ###   ########.fr       */
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

int		outfile_open(int outfile, int type, char *file);
int		infile_open(int outfile, int type, char *file);
int		infile_access(char *infile);
int		outfile_access(char *outfile);

int		files_access(t_list *tokkens);
void	files_clear(t_files *files);

t_files	*new_files(void);
t_pids	*new_pids(void);

char	*add_path(char *cmd, char **env);

void	print_files(t_files *files);
void	print_pids(t_pids *pids);

#endif
