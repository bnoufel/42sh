/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:01 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:16 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_count_search(t_list *list, int nb)
{
	int col;

	col = 1;
	list = list->next;
	while (list)
	{
		if (nb == (*g_global->cursor)->window.ws_col)
		{
			nb = 0;
			col++;
		}
		else if (list->c == '\n')
		{
			nb = 0;
			col++;
		}
		nb++;
		list = list->next;
	}
	return (col);
}

int		ft_read_list2(t_list *first, t_cursor *c)
{
	t_list *list;

	c->res_search = 1;
	ft_putstr_fd("\r\x1b[0K", 0);
	ft_putstr_fd("\r\x1b[1A", 0);
	ft_prompt(c);
	list = first;
	while (list)
	{
		ft_putchar_fd(list->c, 0);
		list = list->next;
	}
	return (1);
}
