/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:03:45 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:03:52 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __JOBS_H
# define __JOBS_H

# ifndef __MINISHELL_H
#  include "minishell.h"
# endif

typedef struct			s_pgid
{
	int					old_pgid;
	int					new_pgid;
	struct s_pgid		*next;
	struct s_pgid		*prev;
}						t_pgid;

typedef struct			s_process
{
	char				*name;
	pid_t				pid;
	bool				completed;
	bool				stopped;
	struct s_process	*next;
}						t_process;

typedef struct			s_job
{
	char				*cmd;
	pid_t				pgid;
	t_process			*process;
	bool				pipe;
	struct s_job		*next;
	struct s_job		*prev;
}						t_job;

/*
** Creation des listes
*/

void					pipe_name(int n);
void					ft_process(int pid, char *name);
void					ft_jobs(int pgid, char *cmd, t_par *cur);
int						ft_pgid(int o_pgid, int n_pgid);
int						display_jobs();
int						ft_kill_jobs();
void					ft_actualize(int pid, bool stopped, bool completed);
int						ft_free_job(t_job **jobs);
int						is_job_complete(t_job *jobs);
int						ft_check_job(t_job *job);
void					ft_free_all_processes(t_job **jobs);
void					ft_move_to_jobs(int pid);

/*
** Job control
*/

void					ft_after_waitpid(int *r, int pdid, char *str, int n);
void					ft_father(int pid, int fg, char *str, t_par *cur);
int						ft_set_signal(int fg);
int						ft_wake_up(t_job **job, int bg);
void					ft_clean_jobs(int pdid, int *r);
void					ft_do_jobs_as_sh(void);
void					ft_after_command_job(int jobs);
void					help_after(t_process *pro, int pdid, int *status);

/*
** FG
*/

int						ft_fg(t_av *av);

/*
** MISC
*/

int						is_only_numerical(char *str);
void					display_process(t_process *pro, int a);
void					ft_rewind(void);
void					end();

t_job					*g_jobs;
t_pgid					*g_pgid;

#endif
