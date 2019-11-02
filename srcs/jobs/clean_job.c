/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:08:11 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:08:12 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

/*
** Free all processes in a Job
*/

void			ft_free_process(t_process **pro)
{
	ft_strdel(&(*pro)->name);
	free((*pro));
	*pro = NULL;
}

void			ft_free_all_processes(t_job **jobs)
{
	t_process *tmp;

	while (*jobs && (*jobs)->process)
	{
		tmp = (*jobs)->process;
		(*jobs)->process = (*jobs)->process->next;
		ft_free_process(&tmp);
	}
}

/*
** Free a job
*/

int				ft_free_job(t_job **jobs)
{
	t_job	*curr;

	curr = *jobs;
	if ((*jobs)->pgid != -1)
	{
		*jobs = (*jobs)->prev;
		(*jobs)->next = curr->next;
		if (curr->next)
			curr->next->prev = *jobs;
		ft_free_all_processes(&curr);
		free(curr->cmd);
		free(curr);
		curr = NULL;
		return (0);
	}
	return (1);
}

/*
** A job is complete if all his process are completed
*/

int				is_job_complete(t_job *jobs)
{
	t_process *pro;

	if (jobs->pgid == -1)
		return (0);
	pro = jobs->process;
	if (!pro)
		return (0);
	while (pro)
	{
		if (pro->completed == 0)
			return (0);
		pro = pro->next;
	}
	return (1);
}

int				ft_kill_jobs(void)
{
	while (g_jobs->prev)
		g_jobs = g_jobs->prev;
	g_jobs = g_jobs->next;
	while (g_jobs)
	{
		if (is_job_complete(g_jobs))
			return (ft_free_job(&g_jobs));
		if (!g_jobs->next)
			break ;
		g_jobs = g_jobs->next;
	}
	while (g_jobs->prev)
		g_jobs = g_jobs->prev;
	return (0);
}
