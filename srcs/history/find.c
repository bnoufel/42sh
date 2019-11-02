/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:59:58 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:16 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int		ft_lstlst(t_list *l1, t_list *l2)
{
	t_list *tmp;
	t_list *head_l2;

	head_l2 = l2;
	while (l1)
	{
		if (l1->c == l2->c)
		{
			tmp = l1;
			while (l2 && tmp && l2->c == tmp->c)
			{
				l2 = l2->next;
				tmp = tmp->next;
			}
			if (!l2 || !l2->next)
				return (1);
			l2 = head_l2;
		}
		l1 = l1->next;
	}
	return (0);
}

static void		ft_paste2(t_list **list, t_list *f, t_list *co, t_cursor *c)
{
	t_list	*tmp;
	t_list	*new;
	int		nb;
	int		i;

	i = 0;
	nb = 0;
	new = ft_copy_linked_list(co, &nb);
	tmp = (*list)->next;
	(*list)->next = new;
	new->prev = *list;
	while (new->next)
	{
		left_down_right_up(" [C", list, c, f);
		new = new->next;
	}
	new->next = tmp;
	tmp->prev = new;
	left_down_right_up(" [C", list, c, f);
}

static void		ft_help(t_list **list, t_cursor *c, t_list *first, t_list *tmp)
{
	c->search = 0;
	while ((*list)->prev)
		*list = (*list)->prev;
	while ((*list)->next->next)
		ft_free_right_node(list);
	ft_paste2(list, first, tmp, c);
	c->search = 0;
	c->res_search = 2;
}

void			ft_help_prompt(t_cursor *c)
{
	ft_putstr_fd("\r\x1b[0K", 0);
	ft_putstr_fd("\r\x1b[1A", 0);
	ft_prompt(c);
}

t_list			*ft_finda(t_cursor *c, t_list *f, char *b, t_list **l)
{
	t_history	*history;
	t_list		*tmp;

	history = c->history;
	while (history->next)
		history = history->next;
	while (history->prev)
	{
		tmp = history->list;
		if (ft_lstlst(tmp, f) == 1)
		{
			(b[0] == '\n' && b[1] == '\0') ?
				ft_help(l, c, f, tmp) : ft_read_list2(tmp, c);
			return (tmp);
		}
		history = history->prev;
	}
	if (b[0] == '\n' && b[1] == '\0')
		c->search = 0;
	c->res_search = (b[0] == '\n' && b[1] == '\0') ? 3 : 0;
	ft_help_prompt(c);
	return (tmp);
}
