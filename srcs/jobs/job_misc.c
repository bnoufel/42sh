/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:08:22 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:08:27 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				ft_check_job(t_job *job)
{
	int			a;
	int			i;
	t_process	*process;

	process = job->process;
	a = 0;
	i = 0;
	if (job->pgid == -1)
		return (0);
	while (process)
	{
		if (process->completed)
			i++;
		a++;
		process = process->next;
	}
	if (a == i)
		return (1);
	else
		return (0);
}

void			ft_move_to_jobs(int pid)
{
	t_process *pro;

	if (g_jobs && g_jobs->pgid == -1 && !g_jobs->next)
		return ;
	while (g_jobs && g_jobs->prev)
		g_jobs = g_jobs->prev;
	while (g_jobs)
	{
		pro = g_jobs->process;
		while (pro)
		{
			if (pro->pid == pid)
				return ;
			pro = pro->next;
		}
		g_jobs = g_jobs->next;
	}
}

void			end(void)
{
	if (g_global->cmdline[0] == '(')
		kill(getpid(), 19);
}

int				ft_set_signal(int fg)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	if (g_global->sub)
	{
		signal(SIGTSTP, SIG_IGN);
	}
	if (fg)
		ft_putchar('\n');
	return (1);
}

int				is_only_numerical(char *str)
{
	int i;

	i = 1;
	if (!str[1])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
