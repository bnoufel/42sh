/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_jobs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:08:39 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:08:41 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			ft_process(int pid, char *name)
{
	t_process *process;
	t_process *tmp;

	if (!(process = (t_process *)malloc(sizeof(t_process))))
		malloc_failed("ft_process");
	process->pid = pid;
	process->completed = false;
	process->stopped = false;
	process->name = NULL;
	if (name && !(process->name = ft_strdup(name)))
		malloc_failed("ft_process");
	if (g_jobs && !g_jobs->process)
	{
		process->next = NULL;
		g_jobs->process = process;
	}
	else
	{
		tmp = g_jobs->process;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = process;
		tmp->next->next = NULL;
	}
}

static t_job	*ft_help_jobs(char *cmd, int pgid)
{
	t_job *job;

	if (!(job = (t_job *)malloc(sizeof(t_job))))
		malloc_failed("ft_jobs");
	job->cmd = NULL;
	if (cmd && !(job->cmd = ft_strdup(cmd)))
		malloc_failed("ft_jobs");
	job->pgid = pgid;
	job->process = NULL;
	return (job);
}

void			ft_jobs(int pgid, char *cmd, t_par *cur)
{
	t_job *job;

	job = ft_help_jobs(cmd, pgid);
	if (!cur)
		job->pipe = false;
	else
		job->pipe = (cur->action[0] == '|') ? 1 : 0;
	if (!g_jobs)
	{
		job->next = NULL;
		job->prev = NULL;
		g_jobs = job;
	}
	else
	{
		while (g_jobs->next)
			g_jobs = g_jobs->next;
		g_jobs->next = job;
		job->prev = g_jobs;
		job->next = NULL;
		g_jobs = g_jobs->next;
	}
}

int				ft_pgid(int o_pgid, int n_pgid)
{
	t_pgid *pgid;

	if (!(pgid = (t_pgid *)malloc(sizeof(t_pgid))))
		malloc_failed("ft_jobs");
	ft_bzero(pgid, sizeof(t_pgid));
	pgid->old_pgid = o_pgid;
	pgid->new_pgid = n_pgid;
	if (!g_pgid)
	{
		pgid->next = NULL;
		pgid->prev = NULL;
		g_pgid = pgid;
	}
	else
	{
		while (g_pgid->next)
			g_pgid = g_pgid->next;
		g_pgid->next = pgid;
		g_pgid->next->prev = g_pgid;
		g_pgid->next->next = NULL;
	}
	return (1);
}
