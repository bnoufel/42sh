/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helptoparse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:39:16 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:39:17 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		parserror(t_par *cur, char *buf, int s)
{
	if (((cur->action[0] == '<' || cur->action[0] == '>')
	&& (!buf[s] || buf[s] == ';')) || cur->action[0] == 41
	|| cur->action[0] == 125 || cur->action[0] == 93
	|| cur->action[0] == ';' || (cur->action[0] && cur->action[0] != '<'
	&& cur->action[0] != '>' && (cur->prev && (cur->prev->action[0]
	|| cur->prev->bg)) && !(cur->ac)) || (cur->action[0] && !cur->ac
	&& (!buf[s] || buf[s] == ';' || !ft_strcmp(cur->action, "&&")
	|| cur->action[0] == '|')) || (!cur->ac && cur->bg)
	|| cur->action[0] == 'K')
	{
		if (cur->action[0] != 'K')
		{
			g_global->ret = 2;
			write(2, "mysh: error near '", 18);
			cur->action[0] ? ft_putstr_fd(cur->action, 2)
			: ft_putstr_fd("&", 2);
			ft_putendl_fd("'", 2);
		}
		return (0);
	}
	return (1);
}

t_par	*newelem(t_par *tmp)
{
	t_par *cur;

	if (!(cur = (t_par *)malloc(sizeof(t_par))))
		malloc_failed("newelem");
	cur->lav = NULL;
	cur->tofree = NULL;
	cur->ac = 0;
	cur->bg = 0;
	cur->math = 0;
	cur->br = 0;
	cur->sub = 0;
	cur->q = 0;
	cur->fd[0] = 0;
	cur->fd[1] = 0;
	ft_bzero(cur->action, sizeof(cur->action));
	cur->next = NULL;
	cur->prev = tmp;
	return (cur);
}

char	*readcase(t_par *cur, char **buf, int s)
{
	int		i;
	int		a;
	char	*new;

	i = 0;
	a = 1;
	new = g_global->stdi || g_global->is_scrpt ? NULL : ft_strdup(" ");
	if (!g_global->sub && !(*buf)[s] && cur->action[0])
	{
		while (a && onlyspaces(new) && !g_global->sig)
		{
			if ((g_global->stdi && (a = gnl(0, &new, 1)))
			|| (g_global->is_scrpt && (a = gnl(g_global->f_fd, &new, 1))))
				;
			else if (!g_global->stdi && !g_global->is_scrpt)
			{
				ft_mini_read(&new, &i, 2, ' ');
				ft_cursorless();
			}
		}
		*buf = substitute(*buf, new);
	}
	else
		ft_strdel(&new);
	return (*buf);
}

int		brkcase(t_par *cur)
{
	if (cur->action[0] == '+')
	{
		write(2, "mysh: file descriptor out of range", 34);
		write(2, ": Bad file descriptor\n", 22);
		return (0);
	}
	return (1);
}

int		noblank(char *buf)
{
	int	i;

	i = 0;
	if (!buf)
		return (-1);
	while (buf[i] && (buf[i] == ' ' || buf[i] == '\t'))
		i++;
	if (!buf[i])
		return (-1);
	return (i);
}
