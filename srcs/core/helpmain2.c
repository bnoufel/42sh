/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmain2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:58:13 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:09 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char		*checkinfo(t_var **var, t_cursor *cursor, char hostname[256])
{
	char *path;

	if (!retenv((*var)->lenv, "HOME") || !(path = ft_getenv("PWD", var))
			|| gethostname(hostname, 255))
	{
		cursor->add_line = 0;
		return (NULL);
	}
	return (path);
}

static void	initloop(int *rd, t_cursor *cursor, t_list **list, t_list **first)
{
	*rd = 0;
	ft_ioctl(cursor);
	ft_init_list(list);
	*first = *list;
	g_global->first = *first;
}

static int	endofloop(t_cursor *cursor, t_list *first, t_list **list,
			char *buff)
{
	if (cursor->search == 1)
	{
		ft_research(cursor, first, list, buff);
		ft_bzero(buff, 8);
		return (1);
	}
	count_and_erase_line(cursor, first, 3);
	return (0);
}

void		count_and_erase_line(t_cursor *cursor, t_list *first, int nb)
{
	int i;

	i = 1;
	if (cursor->col == 1)
		ft_putstr_fd("\r\x1b[0K", 0);
	else
	{
		ft_putstr_fd("\r\x1b[0K", 0);
		while (i < cursor->col && cursor->col < 100)
		{
			ft_putstr_fd("\r\x1b[1A", 0);
			ft_putstr_fd("\r\x1b[0K", 0);
			i++;
		}
	}
	ft_count_line(cursor, first, nb);
}

void		loop(t_cursor *cursor, t_var *var)
{
	int		rd;
	char	*buff;
	t_list	*list;
	t_list	*first;

	initloop(&rd, cursor, &list, &first);
	if (!(buff = (char*)malloc(sizeof(char) * 9)))
		malloc_failed("loop");
	ft_add_cursor(cursor, first, &list, &var);
	ft_bzero(buff, 8);
	g_global->list = &list;
	while ((rd = (int)read(0, buff, 1)) > 0)
	{
		if (helploop(&buff, &rd, cursor))
			continue ;
		helploop2(buff, &list, cursor, var);
		if (endofloop(cursor, first, &list, buff))
			continue ;
		ft_choose_prompt(cursor, var, first);
		ft_bzero(buff, 8);
	}
	ft_strdel(&buff);
}
