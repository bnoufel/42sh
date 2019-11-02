/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:26 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:19 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void		ft_assign(char c, t_list **copy)
{
	(*copy)->c = c;
	(*copy)->next = NULL;
	(*copy)->state = 0;
	(*copy)->selected = 0;
	(*copy)->erase = 0;
	(*copy)->qdbs = 0;
}

static void		ft_shorten(t_parno *p, int *nb, t_list **list)
{
	p->copy->prev = NULL;
	p->head = p->copy;
	p->tmp = p->tmp->next;
	while (p->tmp)
	{
		if (!(p->copy->next = (t_list*)malloc(sizeof(t_list))))
			return (malloc_failed("ft_empty_line"));
		ft_assign(p->tmp->c, &p->copy->next);
		p->copy->next->prev = p->copy;
		p->copy = p->copy->next;
		p->tmp = p->tmp->next;
		(*nb)++;
	}
	p->tmp2 = (*list)->next;
	(*list)->next = p->head;
	p->head->prev = *list;
	while (p->head->next)
		p->head = p->head->next;
}

static void		ft_empty_line(t_list **list, t_cursor *cursor, t_list *first)
{
	t_parno p;
	int		nb;

	p.tmp = NULL;
	nb = 1;
	while ((*list)->prev)
		*list = (*list)->prev;
	while ((*list)->next->next)
		ft_free_right_node(list);
	if (cursor->history->list)
	{
		p.tmp = cursor->history->list;
		if (!(p.copy = (t_list*)malloc(sizeof(t_list))))
			malloc_failed("ft_empty_line");
		ft_assign(p.tmp->c, &p.copy);
		ft_shorten(&p, &nb, list);
		p.head->next = p.tmp2;
		p.tmp2->prev = p.head;
		count_and_erase_line(cursor, first, 3);
		init_cursor(cursor, 0);
		ft_home_end(list, (char[4]){27, 34, 'F', '\0'});
	}
}

int				ft_up_down_history(t_cursor *c, char *b, t_list **l, t_list *f)
{
	if (b[2] == 'B')
	{
		if (c->history->next)
		{
			c->history = c->history->next;
			ft_empty_line(l, c, f);
		}
		return (1);
	}
	else if (b[2] == 'A')
	{
		if (c->history->prev->prev)
		{
			c->history = c->history->prev;
			ft_empty_line(l, c, f);
		}
		return (1);
	}
	return (0);
}
