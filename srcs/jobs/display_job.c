/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_job.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:08:14 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:08:14 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		display_process(t_process *pro, int a)
{
	while (pro)
	{
		if (pro->name[0] == '(')
			return ;
		if (a != 0)
			ft_putstr_fd("     ", 0);
		ft_putnbr_fd(pro->pid, 0);
		if (pro->completed)
			ft_putstr_fd("  done       ", 0);
		else if (pro->stopped)
			ft_putstr_fd("  suspended  ", 0);
		else
			ft_putstr_fd("  working    ", 0);
		ft_putendl_fd(pro->name, 0);
		pro = pro->next;
		a++;
	}
}

int			display_jobs(void)
{
	t_job		*job;
	t_process	*pro;
	int			i;
	int			a;

	ft_do_jobs_as_sh();
	i = 1;
	if (!g_jobs)
		return (1);
	job = g_jobs;
	while (job->prev)
		job = job->prev;
	job = job->next;
	while (job)
	{
		ft_putstr_fd("[", 0);
		ft_putnbr_fd(i, 0);
		ft_putstr_fd("]  ", 0);
		pro = job->process;
		a = 0;
		display_process(pro, a);
		i++;
		job = job->next;
	}
	return (0);
}

void		ft_actualize(int pid, bool stopped, bool completed)
{
	t_job		*job;
	t_process	*pro;

	job = g_jobs;
	while (job)
	{
		pro = job->process;
		while (pro)
		{
			if (pro->pid == pid)
			{
				pro->stopped = stopped;
				pro->completed = completed;
				return ;
			}
			pro = pro->next;
		}
		job = job->next;
	}
}
