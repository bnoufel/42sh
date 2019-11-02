/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpinsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:58 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:59 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		ft_open_sig(void)
{
	int	i;

	i = 0;
	while (++i < 32)
		signal(i, SIG_DFL);
}

void		close_fdmax(void)
{
	int i;

	i = 3;
	while (i <= g_global->fdmax)
		i == g_global->f_fd ? i++ : close(i++);
}

int			exsub(t_par *cur, t_var *var)
{
	char *t;

	if (cur->sub && cur->lav && cur->lav->av[0] == 40)
	{
		(t = ft_strsub(cur->lav->av, 1, (int)ft_strlen(cur->lav->av) - 1))
			? 0 : malloc_failed("forkaction");
		g_global->ret = eval(&t, &var);
		return (1);
	}
	return (0);
}

char		*helpinsub(pid_t pid, int q, int fds[2])
{
	int		status;
	int		pdid;
	char	*str;

	status = 5759;
	setpgid(pid, pid);
	g_global->is_scrpt ? tcsetpgrp(g_global->f_fd, pid) : tcsetpgrp(0, pid);
	(g_global->sub)--;
	while (status == 5759)
	{
		pdid = waitpid(pid, &status, WUNTRACED);
		g_global->is_scrpt ? tcsetpgrp(g_global->f_fd, pid) : tcsetpgrp(0, pid);
		kill(pdid, 19);
	}
	close(fds[1]);
	str = read_fd(fds[0], q);
	g_global->ret = status;
	close(fds[0]);
	return (str);
}
