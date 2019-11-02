/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:07:20 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:07:22 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			dealwfds2(t_par **cur)
{
	t_par *af;

	while ((*cur) && ((*cur)->action[0] == '>' || (*cur)->action[0] == '<'
				|| ft_isdigit((*cur)->action[0])))
	{
		af = *cur;
		while (af->next && af->action[0] == '<')
			af = af->next;
		(*cur) = (*cur)->next;
	}
}

void			bofg(int pid, int *r, t_par *cur, int fd[2])
{
	int			pdid;
	t_process	*pro;

	close_fdmax();
	if (!(cur->bg) && ((pro = g_jobs->process) || !pro))
	{
		while (pro)
		{
			pdid = waitpid(pro->pid, r, WUNTRACED);
			ft_after_waitpid(r, pdid, pro->name, 1);
			pro = pro->next;
		}
		fgend(pdid, r, fd);
	}
	else
	{
		ft_putstr("[+");
		ft_putnbr(pid);
		ft_putstr("] ");
		if (!g_global->pipe)
			ft_putstr(cur->lav->av);
		(*g_global->cursor)->add_line = 0;
		g_global->ret = 1;
		g_global->bg = 1;
	}
}

void			forkaction(t_par *cur, t_var *var, int fd[2])
{
	pid_t			pid;
	char			m[PATH_MAX];

	if ((pid = fork()) == -1)
	{
		ft_putendl_fd("mysh: resource temporarily unavailable", 2);
		g_global->sig = 1;
		return ;
	}
	else if (!pid)
	{
		if (ft_set_signal(cur->bg) && !dealwfds1(cur, fd)
		&& dupinsidefork(cur, fd) && !exsub(cur, var)
		&& (g_global->ret = builtin_command(&cur, &var, fd) > 1))
			exec(var, m, cur);
		g_global->sig = 3;
		ft_bye_bye(&var, 0, NULL, g_global->ret ? 1 : 0);
	}
	ft_father(pid, cur->bg, g_global->cmdline, cur);
	endofexec(&cur, pid, fd);
}

int				takeaction(t_par **par, t_var *var, t_par *cur)
{
	char		*tofree;
	int			fd[2];

	while (cur && !(tofree = NULL))
	{
		if (status(cur, fd) && fncheck(&var, cur)
		&& script_tokenizer(&var, &cur, 0))
		{
			if (!rewriteavs(&cur, var, 0, 0) || execf(&var, cur))
				;
			else if (cur->lav && cur->lav->av[0] == '[')
				ft_compare(cur, &(g_global->ret));
			else if (cur->sub && cur->lav && cur->lav->av[0] == 40 && cur->math)
				tofree = mathcore(ft_strdup(cur->lav->av), var, *par);
			else if (!g_global->sig)
				toforkornot(cur, var, fd)
				? (g_global->ret = 1) : 0;
			if (g_global->sig)
				break ;
		}
		gonext(&cur, &tofree);
	}
	return (g_global->sig ? 1 : g_global->ret);
}
