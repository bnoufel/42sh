/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewriteavs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:39:57 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:39:58 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

t_av			*checkassign(t_par **cur, t_var *var)
{
	t_av *tofree;
	t_av *tmp;

	tofree = (*cur)->lav;
	if (!(*cur)->ac)
		return (0);
	if (!((*cur)->lav = checkifvar(*cur, &var, 1, 0)))
		g_global->ret = 0;
	else
		(*cur)->lav->last->head = (*cur)->lav;
	while (tofree && tofree != (*cur)->lav)
	{
		ft_strdel(&(tofree->av));
		tmp = tofree;
		tofree = tofree->next;
		free(tmp);
		tmp = NULL;
	}
	ft_strdel(&(g_global->cmdline));
	(*cur)->lav ? g_global->cmdline = transform_list_to_char((*cur)->lav) : 0;
	return ((*cur)->lav);
}

static t_av		*subnsplit(t_av **av, t_var *var, int *f, t_par *cur)
{
	int		c;
	char	*tofree;

	c = 1;
	tofree = (*av)->av;
	*f == 3 ? ((*av)->av = glob_core_while((*av)->av, &c, var, 0)) : 0;
	(*f == 3 && tofree && !(*av)->av) ? ft_strdel(&tofree) : 0;
	!g_global->par && *f == 1
		? (*av)->av = cksubmath(&((*av)->av), var, cur, &c) : 0;
	if ((!(*av)->av || !(*av)->av[0]) && (*f = 5))
		return (*av);
	if (((*f == 1 && !g_global->par) || *f == 3) && c)
		*av = splitsub(cur, av, f);
	if (*f == 3 && !c)
	{
		if ((*av)->next)
			return ((*av)->next);
		else
			*f = 5;
	}
	*f == 1 && c ? (*f = 0) : 0;
	return (*av);
}

int				rewriteavs(t_par **cur, t_var *var, int i, int f)
{
	if (!(*cur)->lav)
		return (1);
	if (!((*cur)->lav = checkassign(cur, var)))
		return (g_global->ret);
	if (*cur && (((*cur)->sub && (*cur)->lav && (*cur)->lav->av[0] == 40)
	|| (!(*cur)->lav && (*cur)->action[0])))
		return (1);
	while (f != 5 && (*cur)->lav && (f = 1))
	{
		onebyone(&((*cur)->lav->av), var, 0, 0);
		while ((*cur)->lav && (*cur)->lav->next && !((*cur)->lav->av[0])
				&& ((*cur)->lav = (*cur)->lav->next))
			onebyone(&((*cur)->lav->av), var, 0, 0);
		(*cur)->lav = subnsplit(&((*cur)->lav), var, &f, *cur);
		if ((*cur)->lav->av && !(i++) && (!ft_strcmp((*cur)->lav->av, "export")
		|| !ft_strcmp((*cur)->lav->av, "env")
		|| ((*cur)->sub && (*cur)->lav->av[0] == 40)))
			return (1);
		f && f != 5 ? f += 2 : 0;
		f != 5 ? ((*cur)->lav = subnsplit(&((*cur)->lav), var, &f, *cur)) : 0;
	}
	if ((*cur)->lav && ((*cur)->lav = (*cur)->lav->head))
		cleanlist(&((*cur)->lav));
	return (1);
}
