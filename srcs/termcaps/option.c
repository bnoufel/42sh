/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:59 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:00 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			ft_reset_selection(t_list **list)
{
	t_list *tmp;

	tmp = *list;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp->next)
	{
		tmp->selected = 0;
		tmp = tmp->next;
	}
}

int				ft_home_end(t_list **list, char *buff)
{
	if ((buff[0] == 27 && buff[2] == 'H') || (buff[0] == 1 && buff[1] == 0))
	{
		(*list)->next->state = 0;
		while ((*list)->prev)
			*list = (*list)->prev;
		(*list)->next->state = 1;
		return (1);
	}
	else if ((buff[0] == 27 && buff[2] == 'F')
					|| (buff[0] == 5 && buff[1] == 0))
	{
		(*list)->next->state = 0;
		while ((*list)->next->next)
			*list = (*list)->next;
		(*list)->next->state = 1;
		return (1);
	}
	return (0);
}

void			ft_up_down(t_list **list, t_cursor *c, int n, t_list *first)
{
	int i;
	int count;

	count = 0;
	i = -1;
	while (*list && ++i < c->window.ws_col && count < 1)
	{
		if (n == 0)
		{
			if ((*list)->c == '\n')
				count++;
			left_down_right_up(" [D", list, c, first);
		}
		else
		{
			left_down_right_up(" [C", list, c, first);
			if ((*list)->c == '\n')
				count++;
		}
	}
	if (c->is_selected == 1)
	{
		ft_reset_selection(list);
		c->is_selected = 0;
	}
}

void			ft_option(char *buff, t_list **list, t_cursor *c, t_list *first)
{
	if (ft_strcmp(buff, (char[4]){-30, -119, -120, '\0'}) == 0)
		ft_copy_cut(c, list, 1, first);
	else if (ft_strcmp(buff, (char[3]){-61, -89, '\0'}) == 0)
		ft_copy_cut(c, list, 0, first);
	else if (ft_strcmp(buff, (char[4]){-30, -120, -102, '\0'}) == 0)
		ft_paste(list, c, first);
	else if (ft_strcmp(buff, (char[5]){27, 27, 91, 67, '\0'}) == 0)
		ft_select(list, c, 0, first);
	else if (ft_strcmp(buff, (char[5]){27, 27, 91, 68, '\0'}) == 0)
		ft_select(list, c, 1, first);
	else if (ft_strcmp(buff, (char[5]){27, 27, 91, 65, '\0'}) == 0)
		ft_up_down(list, c, 0, first);
	else if (ft_strcmp(buff, (char[5]){27, 27, 91, 66, '\0'}) == 0)
		ft_up_down(list, c, 1, first);
}
