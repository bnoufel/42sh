/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:20 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:19 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			ft_erase_line(int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		ft_putstr_fd("\r\x1b[0K", 0);
		ft_putstr_fd("\r\x1b[1A", 0);
		i++;
	}
}

void			ft_prompt(t_cursor *c)
{
	ft_info_line(c, g_global->var);
	if (c->res_search == 1)
		ft_putstr_fd("\033[34;1m", 0);
	else if (c->res_search == 0)
		ft_putstr_fd("\033[31;1m", 0);
	else
		ft_putstr_fd("\033[33;1m", 0);
	ft_putstr_fd("$> ", 0);
	ft_putstr_fd("\033[0m", 0);
}

void			ft_e_line(t_cursor *cursor)
{
	int i;

	i = 1;
	ft_putstr_fd("\r\x1b[0K", 0);
	while (i < cursor->col)
	{
		ft_putstr_fd("\r\x1b[1A", 0);
		ft_putstr_fd("\r\x1b[0K", 0);
		i++;
	}
}

static void		dealwresearch(t_cursor *c, int *count_tmp,
				t_list *first, t_list *tmp)
{
	if (c->res_search == 1)
	{
		c->a = 16;
		*count_tmp = (tmp) ? (ft_count_search(tmp, 3)) : 1;
		c->col = ft_count_search(first, 16) + *count_tmp + 1;
		ft_putstr_fd("\nbck-searching : ", 0);
	}
	else if (c->res_search == 0)
	{
		c->a = 23;
		*count_tmp = (tmp) ? (ft_count_search(tmp, 3)) : 1;
		c->col = ft_count_search(first, 23) + *count_tmp + 1;
		ft_putstr_fd("\nfailed bck-searching : ", 0);
	}
	else if (c->res_search == -1)
	{
		c->a = 12;
		if (g_global->sear == 0)
			c->col++;
		g_global->sear++;
		ft_putstr_fd("\nstarting : ", 0);
	}
}

void			ft_research(t_cursor *c, t_list *first, t_list **list, char *b)
{
	int			a;
	t_list		*tmp;
	int			count_tmp;

	a = 1;
	tmp = NULL;
	ft_e_line(c);
	ft_prompt(c);
	if (first->next->c != ' ' || first->next->next)
		tmp = ft_finda(c, first->next, b, list);
	if (c->res_search == 3 || c->res_search == 2)
	{
		c->search = 0;
		c->res_search = -1;
		c->col--;
		ft_read_list(first, c, 3);
		g_global->sear = 0;
		return ;
	}
	else
		dealwresearch(c, &count_tmp, first, tmp);
	ft_read_list(first, c, 3);
}
