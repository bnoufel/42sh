/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:08:03 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:08:05 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void		ft_display_uno(int pdid, char *str)
{
	if (g_global->sub)
		return ;
	ft_putstr_fd("\n ~ ", 2);
	ft_putnbr_fd(pdid, 2);
	ft_putstr_fd(" suspended ", 2);
	ft_putendl_fd(str, 2);
}

static void		ft_display_dos(int pdid, int termsig, int n)
{
	ft_putstr_fd("\n ~ ", 2);
	ft_putnbr_fd(pdid, 2);
	if (termsig == 30)
	{
		ft_putendl_fd("   exit 127", 2);
		return ;
	}
	ft_putstr_fd(" killed by signal ", 2);
	ft_putnbr_fd(termsig, 2);
	ft_putendl_fd("", 2);
	if (n == 0)
		g_global->is_scrpt ? tcsetpgrp(g_global->f_fd, g_pgid->new_pgid)
		: tcsetpgrp(0, g_pgid->new_pgid);
}

void			ft_clean_jobs(int pdid, int *r)
{
	if (WIFEXITED(*r) || WTERMSIG(*r) == SIGINT)
	{
		ft_move_to_jobs(pdid);
		if (g_jobs && (g_global->pipe == 1 || g_jobs->pipe == 1))
			ft_free_job(&g_jobs);
		else if (g_jobs)
			ft_kill_jobs();
	}
}

void			ft_after_waitpid(int *r, int pdid, char *str, int n)
{
	if (WIFSTOPPED(*r))
	{
		ft_actualize(pdid, 1, 0);
		if (g_global->pipe)
		{
			g_global->pipe = 3;
			return ;
		}
		ft_display_uno(pdid, str);
	}
	else if (WIFSIGNALED(*r))
	{
		ft_actualize(pdid, 0, 1);
		if (g_global->pipe)
		{
			g_global->pipe = 3;
			return ;
		}
		if (str[0] == '(')
			return ;
		(WTERMSIG(*r) == 2) ? g_global->sig = 1 : 0;
		(WTERMSIG(*r) != 13) ? ft_display_dos(pdid, WTERMSIG(*r), n) : 0;
	}
	else if (WIFEXITED(*r))
		ft_actualize(pdid, 0, 1);
}
