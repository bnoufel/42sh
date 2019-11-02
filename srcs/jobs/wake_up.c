/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wake_up.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:08:51 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:08:53 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			ft_help_wake(int bg, t_process *tmp, t_job **job)
{
	int			r;
	int			pdid;

	if (getpgid(tmp->pid))
	{
		ft_putstr("   + ");
		ft_putnbr(tmp->pid);
		ft_putstr(" continued ");
		ft_putendl(tmp->name);
	}
	if (bg != 0)
	{
		tmp->stopped = false;
		pdid = waitpid(tmp->pid, &r, WUNTRACED | WNOHANG);
		tcsetpgrp(0, g_pgid->new_pgid);
	}
	else
		pdid = waitpid(tmp->pid, &r, WUNTRACED);
	g_global->jobs = true;
	if (bg == 0)
	{
		ft_after_waitpid(&r, pdid, (*job)->cmd, 0);
		ft_clean_jobs(pdid, &r);
	}
}

int				ft_wake_up(t_job **job, int bg)
{
	t_process	*tmp;

	if (bg == 0)
	{
		if ((!g_global->sub && tcsetpgrp(0, (*job)->pgid) == -1)
		|| tcsetpgrp(g_global->f_fd, (*job)->pgid) == -1)
		{
			ft_putendl_fd("The shell is unable to wake up this process.", 2);
			return (1);
		}
		if (tcsetattr(0, TCSADRAIN, (*g_global->cursor)->old) == -1)
			ft_bye_bye(g_global->var, 0, NULL, 1);
	}
	tmp = (*job)->process;
	while (tmp)
	{
		kill(tmp->pid, SIGCONT);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (!tmp->stopped)
		return (1);
	ft_help_wake(bg, tmp, job);
	return (0);
}
