/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cx_cc_cv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:40 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:40 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void				ft_paste(t_list **list, t_cursor *cursor, t_list *first)
{
	t_list		*tmp;
	t_list		*new;
	int			nb;
	int			i;

	i = 0;
	nb = 0;
	if (cursor->save == NULL)
		return ;
	new = ft_copy_linked_list(cursor->save, &nb);
	tmp = (*list)->next;
	(*list)->next = new;
	new->prev = *list;
	while (new->next)
	{
		left_down_right_up(" [C", list, cursor, first);
		new = new->next;
	}
	new->next = tmp;
	tmp->prev = new;
	left_down_right_up(" [C", list, cursor, first);
}

void				ft_save_node(t_cursor *cursor, t_list **list, int n)
{
	if (!cursor->save)
		cursor->save = ft_copy_node(*list);
	else
	{
		if (n == 0)
		{
			cursor->save->next = ft_copy_node(*list);
			cursor->save->next->prev = cursor->save;
			cursor->save = cursor->save->next;
		}
		else
		{
			cursor->save->prev = ft_copy_node(*list);
			cursor->save->prev->next = cursor->save;
			cursor->save = cursor->save->prev;
		}
	}
}

static void			ft_copy_un(t_list **list, t_cursor *c, t_list *first, int n)
{
	if ((*list)->selected == 0)
	{
		while ((*list)->next->selected == 1)
		{
			left_down_right_up(" [C", list, c, first);
			ft_save_node(c, list, 0);
			if (n == 1)
				ft_free_left_node(list);
		}
		while (c->save->prev)
			c->save = c->save->prev;
	}
	else
	{
		while ((*list)->selected == 1)
		{
			ft_save_node(c, list, 1);
			left_down_right_up(" [D", list, c, first);
			if (n == 1)
				ft_free_right_node(list);
		}
	}
}

void				ft_copy_cut(t_cursor *c, t_list **list, int n, t_list *f)
{
	if (c->save)
	{
		ft_free_all(&c->save);
		c->save = NULL;
	}
	if ((*list)->selected == 0 && (*list)->next->selected != 1)
		return ;
	if ((*list)->state == -1)
		(*list)->selected = 0;
	ft_copy_un(list, c, f, n);
	if (n != 1)
		if (c->is_selected == 1)
		{
			ft_reset_selection(list);
			c->is_selected = 0;
		}
}

void				ft_select(t_list **list, t_cursor *c, int s, t_list *first)
{
	if (s == 0)
	{
		if ((*list)->next->next)
		{
			c->is_selected = 1;
			if ((*list)->next->selected == 0)
				(*list)->next->selected = 1;
			else
				(*list)->next->selected = 0;
			left_down_right_up(" [C", list, c, first);
		}
	}
	else
	{
		c->is_selected = 1;
		if ((*list)->selected == 0)
			(*list)->selected = 1;
		else
			(*list)->selected = 0;
		left_down_right_up(" [D", list, c, first);
	}
}
