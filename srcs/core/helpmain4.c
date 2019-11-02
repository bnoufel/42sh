/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmain4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:59:08 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:10 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char	*ft_return_home(char *str)
{
	int i;

	i = (int)ft_strlen(str);
	while (i > 0 && str[i] != '/')
		i--;
	if (str[i] == '/')
		i++;
	return (str + i);
}

void	ft_add_cursor(t_cursor *cursor, t_list *first,
		t_list **list, t_var **var)
{
	ft_add_elem(list, ' ', NULL);
	(*list)->next->state = 1;
	ft_putstr_fd("\r\x1b[0K", 0);
	ft_info_line(cursor, var);
	ft_read_list(first, cursor, 1);
	cursor->col += cursor->add_line;
}

void	ft_count_line(t_cursor *cursor, t_list *list, int nb)
{
	cursor->col = 1 + cursor->add_line;
	if (!list || !list->next || !list->next->next)
		return ;
	list = list->next;
	while (list)
	{
		if (nb == cursor->window.ws_col)
		{
			nb = 0;
			cursor->col++;
		}
		else if (list->c == '\n')
		{
			if (list->next && list->next->erase == 1)
				nb = 0;
			else
				nb = -1;
			cursor->col++;
		}
		nb++;
		list = list->next;
	}
}

void	exit_term(t_var **var)
{
	freevar(*var);
	clean_tab();
	clean_bin();
	exit(1);
}
