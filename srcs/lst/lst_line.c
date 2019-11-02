/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:52 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:53 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char			*ft_list_to_string(t_list *list, int n)
{
	char		*str;
	t_list		*head;

	if (n == 1)
		while (list->prev)
			list = list->prev;
	head = list;
	if (!(str = ft_strnew(1)))
		malloc_failed("ft_list_to_string");
	while (head->next)
	{
		if (head->c == '\n' && head->qdbs == 1)
		{
			if (!(str = ft_strjoinfree(str, ft_chardup(';'), 3)))
				malloc_failed("ft_list_to_string");
		}
		else if (!((head->c == '>' && head->erase == 1)
		|| (head->c == '\n' && head->qdbs == 2)))
			if (!(str = ft_strjoinfree(str, ft_chardup(head->c), 3)))
				malloc_failed("ft_list_to_string");
		head = head->next;
	}
	if (!(str = ft_strjoinfree(str, " ", 1)))
		malloc_failed("ft_list_to_string");
	return (str);
}

void			ft_color(int n)
{
	if (n == 0)
		ft_putstr_fd("\033[41;30m", 0);
	else if (n == 1)
		ft_putstr_fd("\033[42;30m", 0);
	else if (n == 2)
		ft_putstr_fd("\033[43;30m", 0);
	else if (n == 3)
		ft_putstr_fd("\033[44;30m", 0);
	else if (n == 4)
		ft_putstr_fd("\033[45;30m", 0);
	else if (n == 5)
		ft_putstr_fd("\033[46;30m", 0);
	else if (n == 6)
		ft_putstr_fd("\033[47;34m", 0);
}

void			ft_read_list(t_list *first, t_cursor *cursor, int a)
{
	t_list *list;

	list = first;
	if (a != 3 && a != 4)
	{
		ft_putstr_fd("$", 0);
		if (g_global->ret == 0)
			ft_putstr_fd("\033[32m", 0);
		else
			ft_putstr_fd("\033[31m", 0);
		ft_putstr_fd(">", 0);
		ft_putstr_fd("\033[0m ", 0);
	}
	while ((list = list->next))
	{
		if (list->prev && list->prev->erase == 1)
			ft_putchar_fd(' ', 0);
		if (a != 0 && a != 4 && list->state != 0)
			ft_color(cursor->color);
		else if (a != 0 && a != 4 && list->selected == 1)
			ft_putstr_fd("\033[47;30m", 0);
		ft_putchar_fd(list->c, 0);
		if ((a != 0) && a != 4 && (list->state == 1 || list->selected == 1))
			ft_putstr_fd("\033[0m", 0);
	}
}

void			ft_init_list(t_list **list)
{
	if (!(*list = (t_list *)malloc(sizeof(t_list))))
		return (malloc_failed("ft_init_list"));
	(*list)->next = NULL;
	(*list)->prev = NULL;
	(*list)->state = -1;
	(*list)->erase = 0;
	(*list)->qdbs = 0;
	(*list)->selected = 0;
	(*list)->c = '\0';
}
