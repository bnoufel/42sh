/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:03 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:17 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

t_list		*ft_struct(char c, int n)
{
	t_list *new;

	new = NULL;
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		malloc_failed("ft_struct");
	ft_bzero(new, sizeof(t_list));
	new->c = c;
	new->state = n;
	new->selected = 0;
	new->next = NULL;
	new->prev = NULL;
	new->erase = 0;
	return (new);
}

t_list		*ft_transform(char *str)
{
	t_list	*new;
	t_list	*head;
	int		i;

	i = 0;
	new = ft_struct(str[i], 1);
	new->next = NULL;
	new->prev = NULL;
	head = new;
	i++;
	while (str[i])
	{
		new->next = ft_struct(str[i], 0);
		new->next->prev = new;
		new = new->next;
		i++;
	}
	return (head);
}

void		ft_close(t_cursor *cursor)
{
	t_list	*list;
	char	c;

	if ((cursor->fd = open(cursor->path, O_APPEND | O_CREAT
	| O_RDWR, 0600)) == -1)
		return (ft_putendl_fd("mysh : Can't save history", 2));
	while (cursor->history->prev)
		cursor->history = cursor->history->prev;
	while (cursor->history->next)
	{
		if (cursor->history->file == 0)
		{
			list = cursor->history->list;
			while (list)
			{
				c = list->c;
				write(cursor->fd, &c, 1);
				list = list->next;
			}
			write(cursor->fd, "\n", 1);
		}
		cursor->history = cursor->history->next;
	}
	free(cursor->path);
	close(cursor->fd);
}

void		loop_gnl(t_cursor *cursor)
{
	int			rd;
	char		*line;

	while ((rd = gnl(cursor->fd, &line, 0)) > 0)
	{
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}
		if (!(cursor->history->next = (t_history*)malloc(sizeof(t_history))))
			malloc_failed("ft_open");
		ft_bzero(cursor->history->next, sizeof(t_history));
		cursor->history->next->prev = cursor->history;
		cursor->history = cursor->history->next;
		cursor->history->list = ft_transform(line);
		cursor->history->head = 0;
		cursor->history->file = 1;
		free(line);
	}
	close(cursor->fd);
}

void		ft_open(t_cursor *cursor)
{
	char		*tmp;

	tmp = ft_getenv("HOME", g_global->var);
	if (!(cursor->path = ft_strjoin(tmp,
		tmp && tmp[ft_strlen(tmp) - 1] == '/' ? ".myhistory" : "/.myhistory")))
		malloc_failed("strjoin open");
	cursor->fd = open(cursor->path, O_CREAT | O_RDWR, 0600);
	cursor->history = ft_init_history();
	if (cursor->fd != -1)
		loop_gnl(cursor);
	cursor->history->next = ft_init_history();
	cursor->history->next->prev = cursor->history;
	cursor->history = cursor->history->next;
}
