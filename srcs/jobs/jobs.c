/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:08:32 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:08:34 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			ft_rewind(void)
{
	while (g_jobs->prev)
		g_jobs = g_jobs->prev;
}

void			ft_father(int pid, int fg, char *str, t_par *cur)
{
	t_job		*jj;

	if (g_global->jobs)
	{
		ft_jobs(pid, str, cur);
		g_global->jobs = false;
		setpgid(pid, pid);
		if (!fg)
			g_global->is_scrpt ? tcsetpgrp(g_global->f_fd, pid)
			: tcsetpgrp(0, pid);
	}
	else
	{
		jj = g_jobs;
		while (jj && jj->next)
			jj = jj->next;
		jj ? setpgid(pid, jj->pgid) : 0;
		if (!g_global->pipe && fg == 1 && jj)
			g_global->is_scrpt ? tcsetpgrp(g_global->f_fd, jj->pgid)
			: tcsetpgrp(0, jj->pgid);
	}
	ft_process(pid, str);
	if (cur->action[0] == '\0' && cur->next)
		g_global->jobs = true;
}

void			ft_cleanse_job(int display)
{
	t_job *job;

	job = g_jobs;
	while (g_jobs)
	{
		if (ft_check_job(g_jobs))
		{
			if (display)
				display_process(g_jobs->process, 0);
			ft_free_job(&g_jobs);
		}
		if (!g_jobs->next)
			break ;
		g_jobs = g_jobs->next;
	}
	g_jobs = job;
}

void			ft_do_jobs_as_sh(void)
{
	t_job		*job;
	t_process	*pro;
	int			status;
	int			pdid;

	status = 0;
	ft_rewind();
	if (!g_jobs->next)
		return ;
	ft_cleanse_job(0);
	if (g_jobs->next)
		g_jobs = g_jobs->next;
	job = g_jobs;
	while (job)
	{
		pro = job->process;
		while (pro)
		{
			pdid = waitpid(pro->pid, &status, WNOHANG);
			ft_after_waitpid(&status, pdid, pro->name, 1);
			pro = pro->next;
		}
		job = job->next;
	}
}

void			ft_after_command_job(int jobs)
{
	t_job		*job;
	t_process	*pro;
	int			status;
	int			pdid;

	ft_rewind();
	if (!(status = 0) && (!g_jobs->next || jobs))
		return ;
	(g_jobs->next) ? g_jobs = g_jobs->next : 0;
	job = g_jobs;
	while (job && ((pro = job->process) || !pro))
	{
		while (pro)
		{
			pdid = waitpid(pro->pid, &status, WUNTRACED | WNOHANG);
			help_after(pro, pdid, &status);
			pro = pro->next;
		}
		if (g_global->pipe == 3 && !(g_global->pipe = 0))
			pipe_name(1);
		job = job->next;
	}
	ft_rewind();
	ft_cleanse_job(1);
}
