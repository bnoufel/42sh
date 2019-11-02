/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helptoparse4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:39:36 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:39:37 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			outofrec(char **s, int *i, char c, t_par *cur)
{
	int		p;

	(*i)--;
	if (!outofrecfd(s, &p, c, cur))
		return (0);
	else if (!p && (c == 96 || c == 34 || c == 39))
	{
		*i = c == 96 ? ft_mini_read(s, i, 1, ';')
			: ft_mini_read(s, i, 3, '\n');
		ft_cursorless();
	}
	else if (!p && !g_global->stdi && !g_global->is_scrpt
	&& (c == 41 || c == 125 || c == 93))
	{
		*i = !cur->math ? ft_mini_read(s, i, 1, ';')
		: ft_mini_read(s, i, 2, ' ');
		ft_cursorless();
	}
	return (1);
}

static void	helpsplitsub(t_av **av, t_par **temp, t_av **save)
{
	char	*tosplit;

	*temp = NULL;
	g_global->par = 2;
	(tosplit = ft_strjoin((*av)->av, " ")) ? 0 : malloc_failed("helpsplitsub");
	parseline(&tosplit, temp);
	g_global->par = 0;
	ft_strdel(&tosplit);
	*save = (*temp)->lav->last;
}

t_av		*splitsub(t_par *cur, t_av **av, int *f)
{
	t_par	*temp;
	t_av	*save;

	helpsplitsub(av, &temp, &save);
	temp->lav->prev = (*av)->prev;
	temp->lav->last->next = (*av)->next;
	if ((*av)->next)
	{
		(*av)->next->prev = temp->lav->last;
		changelast(&(temp->lav), av);
	}
	if ((*av)->prev)
	{
		(*av)->prev->next = temp->lav;
		changehead(&(temp->lav), av);
	}
	else if ((*av)->next)
		changehead(&(cur->lav), &(temp->lav));
	cur->ac = temp->ac + cur->ac - 1;
	ft_strdel(&((*av)->av));
	free(*av);
	*av = !temp->lav->prev ? temp->lav : NULL;
	temp->next = cur->tofree;
	cur->tofree = temp;
	return (*f == 1 ? save : temp->lav);
}

int			nbcks(char *s, int b)
{
	int i;
	int	a;

	i = 0;
	a = b;
	while (s[a] == 92)
	{
		i++;
		if (!a)
			break ;
		a--;
	}
	return (i % 2);
}

void		cleanlist(t_av **av)
{
	t_av	*iter;
	int		f;
	char	*temp;

	f = 0;
	iter = *av;
	while (f != 5 && iter)
	{
		temp = bckslshav(iter->av, chardelim(iter->av));
		ft_strdel(&(iter->av));
		iter->av = temp;
		if (iter->next)
			iter = iter->next;
		else
			f = 5;
	}
}
