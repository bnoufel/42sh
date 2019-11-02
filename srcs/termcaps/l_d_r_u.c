/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_d_r_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:56 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:57 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void		ft_left(t_list **list)
{
	if ((*list)->prev && (*list)->c == '\n')
	{
		if ((*list) && (*list)->erase == 1)
			return ;
		(*list)->next->state = 0;
		*list = (*list)->prev;
		(*list)->next->state = 1;
	}
	if ((*list)->prev)
	{
		if ((*list) && (*list)->erase == 1)
			return ;
		(*list)->next->state = 0;
		*list = (*list)->prev;
		(*list)->next->state = 1;
	}
}

static void		ft_right(t_list **list)
{
	if ((*list)->next->next && (*list)->next->next->c == '\n')
	{
		*list = (*list)->next;
		(*list)->state = 0;
		(*list)->next->state = 1;
	}
	if ((*list)->next->next)
	{
		*list = (*list)->next;
		(*list)->state = 0;
		(*list)->next->state = 1;
	}
}

int				left_down_right_up(char *b, t_list **l, t_cursor *c, t_list *f)
{
	if (b[1] == '[')
	{
		if (c->search != 1 && ft_up_down_history(c, b, l, f) == 1)
			return (1);
		else if (b[2] == 'C')
		{
			ft_right(l);
			return (1);
		}
		else if (b[2] == 'D')
		{
			ft_left(l);
			return (1);
		}
	}
	return (0);
}
