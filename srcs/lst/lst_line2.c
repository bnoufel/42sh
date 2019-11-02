/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_line2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:53 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:54 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			ft_free_all(t_list **list)
{
	if (*list)
		ft_free_all(&(*list)->next);
	free(*list);
	*list = NULL;
}

void			ft_free_right_node(t_list **list)
{
	t_list *tmp;

	if ((*list)->next->next && (*list)->next->next->c == '\n')
	{
		tmp = (*list)->next;
		(*list)->next = (*list)->next->next;
		(*list)->next->prev = *list;
		(*list)->next->state = 1;
		free(tmp);
	}
	if ((*list)->next->next)
	{
		tmp = (*list)->next;
		(*list)->next = (*list)->next->next;
		(*list)->next->prev = *list;
		(*list)->next->state = 1;
		free(tmp);
	}
}

void			ft_free_left_node(t_list **list)
{
	t_list *tmp;

	if ((*list)->prev && (*list)->c == '\n')
	{
		if ((*list) && (*list)->erase == 1)
			return ;
		*list = (*list)->prev;
		tmp = (*list)->next;
		(*list)->next = (*list)->next->next;
		(*list)->next->prev = *list;
		(*list)->next->state = 1;
		free(tmp);
	}
	if ((*list)->prev)
	{
		if ((*list) && (*list)->erase == 1)
			return ;
		*list = (*list)->prev;
		tmp = (*list)->next;
		(*list)->next = (*list)->next->next;
		(*list)->next->prev = *list;
		(*list)->next->state = 1;
		free(tmp);
	}
}

void			ft_add_elem(t_list **list, char c, t_list *next)
{
	t_list *new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (malloc_failed("ft_add_elem"));
	ft_bzero(new, sizeof(t_list));
	new->prev = *list;
	new->next = next;
	if (next)
		next->prev = new;
	new->c = c;
	new->state = 0;
	new->qdbs = 0;
	new->erase = 0;
	new->selected = 0;
	(*list)->next = new;
}
