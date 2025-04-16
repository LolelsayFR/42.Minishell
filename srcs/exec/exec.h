/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artgirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:06:32 by artgirar          #+#    #+#             */
/*   Updated: 2025/04/16 16:09:41 by artgirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.function.h"

typedef struct s_pipe
{
	int				pipe[2];
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_ex_data
{
	t_pipe	*pipes;
	t_list	*save;
	int		*pid;
	int		*file;
	int		nb_cmd;
	int		i;
}	t_ex_data;

int			outfile_open(int outfile, int type, char *file);
int			infile_open(int outfile, int type, char *file);

char		*tokken_join_id(t_list *tokkens, int id);
char		**tokken_id_join(t_list *tokkens, int id);
t_list		*first_in_id(t_list *tokkens, int id);

int			find_nb_cmd(t_list *data);
int			*find_previous_pipe(t_ex_data *data, int *pipe);

void		wait_all_pids(t_ex_data *data);

int			files_access(t_list *tokkens);

char		*add_path(t_ms_data *data, char *cmd);

t_pipe		*pipe_init(void);

int			arg_nb(t_list *tokkens, int id);
int			numb_of_no_nl(char **tab);

void		do_echo(t_ms_data *data, t_ms_tokken *tokken);
void		do_unset(t_ms_data *data, t_ms_tokken *tokken);
void		do_export(t_ms_data *data, t_ms_tokken *tokken);
void		do_cd(t_ms_data *data, t_ms_tokken *tokken);
void		do_exit(t_ms_data *data, t_ms_tokken *tokken);

t_ex_data	*exec_init(t_list *tokkens);
void		exec_end(t_ex_data *data);
void		free_ex_data(t_ex_data *data);
void		exec_close(t_ex_data *ex_data, char **tab, int status, int err);

//Part of exec_one

int			find_one_infile(t_list *tokkens);
int			find_one_outfile(t_list *tokkens);
t_list		*find_cmd(t_list *tokkens);
void		free_tab_err(char **tab);

void		choose_files(int infile, int outfile);

char		*ft_strjointab(char **tab);

#endif
