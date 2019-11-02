/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:58:08 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:08 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			term1(int *shell_pgid, int *shell_is_interactive, int *o_pgid)
{
	*o_pgid = getpgrp();
	*shell_is_interactive = isatty(1);
	if (*shell_is_interactive)
	{
		*shell_pgid = getpid();
		if (setpgid(*shell_pgid, *shell_pgid) < 0)
		{
			ft_putendl_fd("Job Control failed", 2);
			return (1);
		}
		tcsetpgrp(0, *shell_pgid);
		ft_pgid(*o_pgid, *shell_pgid);
	}
	return (0);
}

int			term2(t_var **var)
{
	char	*s;
	int		i;

	i = 0;
	g_global->sig = 0;
	tcsetpgrp(0, getpid());
	while (++i < 32)
		signal(i, SIG_DFL);
	signal(SIGINT, sig_h);
	g_global->stdi = 1;
	while (gnl(0, &s, 1) > 0)
	{
		if (skip_comment(&s) != 2)
			eval(&s, var);
	}
	return (1);
}

void		ft_realloc_term(char **str, char c)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * 9)))
		malloc_failed("ft_realloc_term");
	tmp[i] = c;
	while (++i < 8)
		tmp[i] = (*str)[i - 1];
	free(*str);
	*str = tmp;
}

int			helploop(char **buff, int *rd, t_cursor *cursor)
{
	char c;

	ft_ioctl(cursor);
	(*buff)[*rd] = '\0';
	if ((*buff)[0] == 27 || (*buff)[0] < 0)
	{
		c = (*buff)[0];
		*rd = read(0, *buff, 7);
		(*buff)[*rd] = '\0';
		ft_realloc_term(buff, c);
	}
	if ((*buff)[0] != 27 && (*buff)[0] != '\n' && (*buff)[0] != 18
			&& (*buff)[0] < 32 && (*buff)[0] > 0 && (*buff)[0] != 4
			&& (*buff)[0] != '\t' && (*buff)[0] != 1 && (*buff)[0] != 5
			&& (*buff)[0] != 12)
		return (1);
	return (0);
}

void		helploop2(char *buff, t_list **list, t_cursor *cursor, t_var *var)
{
	if (ft_is_what_i_want(buff, list, cursor, &var) == false)
	{
		cursor->job = 0;
		ft_add_elem(list, buff[0], (*list)->next);
		*list = (*list)->next;
		cursor->completion = 0;
	}
	if (g_global->sig == 1)
	{
		while (cursor->history->next)
			cursor->history = cursor->history->next;
		init_cursor(cursor, 0);
		ft_free_left_node(list);
		g_global->sig = 0;
	}
}
