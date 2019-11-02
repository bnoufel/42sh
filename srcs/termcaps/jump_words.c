/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:55 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:55 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		ft_left_word(t_list **list, char *buff, t_cursor *c, t_list *first)
{
	if (c->is_selected == 1)
	{
		ft_reset_selection(list);
		c->is_selected = 0;
	}
	while ((*list)->prev && (*list)->c == ' ' && (*list)->c != '>')
		left_down_right_up(buff, list, c, first);
	while ((*list)->prev && (*list)->c != ' ' && (*list)->c != '>')
		left_down_right_up(buff, list, c, first);
}

void		ft_right_word(t_list **l, char *buff, t_cursor *c, t_list *first)
{
	if (c->is_selected == 1)
	{
		ft_reset_selection(l);
		c->is_selected = 0;
	}
	while ((*l)->next->next && (*l)->next->c != ' ' && (*l)->c != '>')
		left_down_right_up(buff, l, c, first);
	while ((*l)->next->next && (*l)->next->c == ' ' && (*l)->c != '>')
		left_down_right_up(buff, l, c, first);
}
