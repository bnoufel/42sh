/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:57:57 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:06 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static	int		ckparav(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 40 && (!i || (!nbcks(s, i - 1) && !hckp(s, i))))
			return (1);
		i++;
	}
	return (0);
}

void			newav(t_par *cur, char *buf, int e, int s)
{
	t_av *new;

	new = cur->lav;
	if (!new)
	{
		if (!(new = (t_av *)malloc(sizeof(t_av))))
			malloc_failed("newav");
		if (!(new->av = ft_strsub(buf, s, e - s)))
			malloc_failed("newav");
		new->next = NULL;
		new->last = new;
		new->head = new;
		cur->lav = new;
		new->prev = NULL;
	}
	else
		fillav(cur, buf, e, s);
	cur->ac++;
	if (!g_global->par && cur->lav && cur->ac > 1 && (ckparav(cur->lav->av)
	|| ckparav(cur->lav->last->av)))
		ft_strcpy(cur->action, ")");
}

int				parseline(char **buf, t_par **par)
{
	t_par	*tmp;
	t_par	*cur;
	int		brk;
	int		e;
	int		s;

	brk = 0;
	tmp = NULL;
	cur = newelem(tmp);
	*par = cur;
	if ((s = noblank(*buf)) == -1)
		return (0);
	while (((e = avdelim(buf, &cur, &brk, s)) >= 0) && *buf && (*buf)[e])
	{
		(e != s) ? newav(cur, *buf, e, s) : 0;
		s = e + newbuf((*buf) + e, &brk, &cur);
		if ((cur->ac && brk && !brkcase(cur))
		|| !parserror(cur, *buf, s)
		|| (!(*buf = readcase(cur, buf, s)) && cur->action[0]))
			return (0);
		cleanbrk(&cur, &tmp, (*buf) + s, brk);
	}
	return (g_global->sig ? 0 : 1);
}

static int		parser(char **cmdline, t_par *par, t_var **var)
{
	if (!parseline(cmdline, &par))
	{
		ft_strdel(cmdline);
		ft_plist_clear(&par);
		return (1);
	}
	ft_strdel(cmdline);
	takeaction(&par, *var, par);
	freefds();
	ft_plist_clear(&par);
	return (0);
}

int				eval(char **cmdline, t_var **var)
{
	t_par		*par;

	par = NULL;
	if ((*var) && (*var)->tenv)
	{
		ft_free_tab((*var)->tenv);
		(*var)->tenv = NULL;
	}
	(*var)->tenv = adaptarray(var);
	(*cmdline)[0] ? (*cmdline)[ft_strlen(*cmdline) - 1] = ' ' : 0;
	if (parser(cmdline, par, var))
		return (g_global->sig || g_global->ret ? 1 : 0);
	return (g_global->ret);
}
