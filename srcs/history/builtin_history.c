/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:59:54 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:16 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void		ft_display_histo(int i, t_list *list)
{
	ft_putnbr(i);
	ft_putchar('\t');
	while (list)
	{
		ft_putchar(list->c);
		list = list->next;
	}
	ft_putchar('\n');
}

int				ft_history(void)
{
	t_history	*histo;
	t_list		*list;
	int			i;

	i = 1;
	histo = (*g_global->cursor)->history;
	if (!histo)
		return (1);
	while (histo->prev->prev)
		histo = histo->prev;
	while (histo->list)
	{
		list = histo->list;
		ft_display_histo(i, list);
		i++;
		histo = histo->next;
	}
	return (0);
}
