/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_before_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:01:01 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:01 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		ft_qdbs(t_cursor *cursor, t_list **list, t_list *first, int qdbs)
{
	if (qdbs == 4)
		qdbs = 2;
	if (!list || !(*list) || !(*list)->next)
		return ;
	while ((*list)->next->next)
		left_down_right_up(" [C", list, cursor, first);
	ft_add_elem(list, ' ', (*list)->next);
	*list = (*list)->next;
	ft_add_elem(list, '\n', (*list)->next);
	*list = (*list)->next;
	(*list)->qdbs = qdbs;
	ft_add_elem(list, '>', (*list)->next);
	*list = (*list)->next;
	(*list)->erase = 1;
}

int			ft_cursorless(void)
{
	int i;

	i = 0;
	if (g_global->sig == 1)
	{
		while (++i < (*g_global->cursor)->col)
		{
			ft_putstr_fd("\r\x1b[1A", 0);
			ft_putstr_fd("\r\x1b[0K", 0);
		}
		return (0);
	}
	count_and_erase_line((*g_global->cursor), g_global->first, 3);
	ft_info_line((*g_global->cursor), g_global->var);
	ft_read_list(g_global->first, (*g_global->cursor), 0);
	ft_putchar_fd('\n', 0);
	return (1);
}

int			ft_check_before_launch(char **str)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while ((*str)[i])
	{
		if (len > LINE_MAX)
		{
			ft_strdel(str);
			return (0);
		}
		if ((*str)[i] == ';')
			len = 0;
		if ((*str)[i] == ' ')
			len = 0;
		i++;
		len++;
	}
	return (1);
}

int			ft_check_before_2(char **str)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while ((*str)[i])
	{
		if (len >= NAME_MAX)
		{
			ft_strdel(str);
			return (0);
		}
		if ((*str)[i] == ' ')
			len = 0;
		i++;
		len++;
	}
	return (1);
}
