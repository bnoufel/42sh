/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:01:02 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:03 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void			link_help(t_list **new, t_list **tmp, int *nb)
{
	(*new)->next = ft_copy_node(*tmp);
	if ((*tmp)->c == '\n' && (*tmp)->qdbs == 1)
		(*new)->next->c = ';';
	(*new)->next->prev = *new;
	*new = (*new)->next;
	(*nb)++;
}

static t_list		*ft_copy_linked_list2(t_list *list, int *nb)
{
	t_list *new;
	t_list *tmp;
	t_list *head;

	if (!(tmp = list))
		return (NULL);
	new = ft_copy_node(list);
	head = new;
	(*nb)++;
	while ((tmp = tmp->next))
	{
		if ((tmp->c == '>' && tmp->next->c == ' '
		&& !tmp->next->next) || (tmp->c == ' ' && !tmp->next))
			return (head);
		if (tmp->qdbs == 1 && tmp->c == '\n'
		&& tmp->prev->c == ' ' && tmp->prev->prev->prev->c == '\n')
			continue ;
		if (tmp->c == ' ' && tmp->next
		&& tmp->next->c == '\n' && tmp->next->next->next->c == ' ')
			continue ;
		if (tmp->erase != 1)
			link_help(&new, &tmp, nb);
	}
	return (head);
}

int					is_empty(t_list *list)
{
	while (list->next)
	{
		if (list->c != ' ')
			return (0);
		list = list->next;
	}
	return (1);
}

static t_list		*help(t_list *list)
{
	t_list *head;

	head = list;
	while (list->next && list->next->next)
		list = list->next;
	if (list && list->next && list->next->c == ' ')
	{
		free(list->next);
		list->next = NULL;
	}
	return (head);
}

void				ft_hist_next(t_cursor *c, t_list *f, t_list *list)
{
	t_history	*tmp;
	int			nb;

	nb = 0;
	while (c->history->next)
		c->history = c->history->next;
	if (list->c == '\0')
		return ;
	if (is_empty(f->next))
		return ;
	tmp = c->history->prev;
	if (!(c->history->prev = (t_history*)malloc(sizeof(t_history))))
		return (malloc_failed("ft_hist_next1"));
	ft_bzero(c->history->prev, sizeof(t_history));
	c->history->prev->next = c->history;
	if (!(c->history->prev->list = help(ft_copy_linked_list2(f->next, &nb))))
		return (malloc_failed("ft_hist_next2"));
	c->history->prev->file = 0;
	c->history->prev->prev = tmp;
	tmp->next = c->history->prev;
	c->history->head = 0;
}
