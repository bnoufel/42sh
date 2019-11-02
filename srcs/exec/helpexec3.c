/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpexec3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:07:50 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:07:51 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	pipe_name(int n)
{
	t_process	*pro;
	char		*str;

	str = ft_strnew(1);
	pro = g_jobs->process;
	while (pro)
	{
		if (n == 1)
		{
			ft_putnbr(pro->pid);
			ft_putchar(' ');
		}
		str = ft_strjoinfree(str, pro->name, 1);
		if (pro->next)
			str = ft_strjoinfree(str, " | ", 1);
		pro = pro->next;
	}
	if (n == 1)
		ft_putstr("\n + suspended ");
	ft_putendl(str);
	ft_strdel(&str);
}

void	fgend(int pdid, int *r, int fd[2])
{
	if (g_jobs && g_jobs->process && g_jobs->process->name
	&& g_jobs->process->name[0] == '(')
	{
		setpgid(pdid, pdid);
		tcsetpgrp(0, pdid);
		while (*r == 5759)
		{
			pdid = waitpid(pdid, r, WUNTRACED | WNOHANG);
			ft_after_waitpid(r, pdid, "subshell", 1);
			tcsetpgrp(0, pdid);
			kill(pdid, 19);
		}
		g_global->ret = *r;
	}
	freefds();
	g_global->fds = NULL;
	ft_clean_jobs(pdid, r);
	g_global->jobs = true;
	g_global->pipe = 0;
	g_global->ret = *r;
	pipensavemax(fd);
}

int		hashkey(t_par **cur, char **gs)
{
	t_par	*topar;
	t_av	*keep;
	t_av	*tmp;
	char	*path;

	topar = NULL;
	if ((*gs)[0] && (*gs)[0] == '#' && (*gs)[1] && (*gs)[1] == '!')
	{
		(path = ft_strdup(*gs + 2)) ? 0 : malloc_failed("hashkey");
		g_global->par = 2;
		parseline(&path, &topar);
		ft_strdel(&path);
		g_global->par = 0;
		if (!topar->lav->av[0] || access(topar->lav->av, X_OK))
		{
			ft_plist_clear(&topar);
			ft_putendl_fd("mysh : bad interpreter", 2);
			return (2);
		}
		return (filllav(&keep, &topar, cur, &tmp));
	}
	else if (!(*gs)[0] || (*gs)[0] == '#')
		return (1);
	return (noshellbang(cur, &topar, 0));
}

void	pushfd(t_par *cur)
{
	t_fds *new;
	t_fds *new2;

	(new = (t_fds *)malloc(sizeof(t_fds))) ? 0 : malloc_failed("pushfd");
	new->fd = cur->fd[0];
	new->next = g_global->fds ? g_global->fds : NULL;
	g_global->fds = new;
	(new2 = (t_fds *)malloc(sizeof(t_fds))) ? 0 : malloc_failed("pushfd");
	new2->fd = cur->fd[1];
	new2->next = g_global->fds;
	g_global->fds = new2;
}

int		notthisone(t_par *cur)
{
	t_fds *iter;

	iter = g_global->fds;
	while (iter)
	{
		if (iter->fd == cur->fd[0] || iter->fd == cur->fd[1])
			return (1);
		iter = iter->next;
	}
	return (0);
}
