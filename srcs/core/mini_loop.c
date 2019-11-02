/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:59:26 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:46 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static	int		minihelp(char **buff)
{
	if (g_global->sig == 1)
	{
		ft_strdel(buff);
		return (0);
	}
	ft_ioctl((*g_global->cursor));
	if ((*buff)[0] == '\n')
		return (1);
	return (2);
}

static void		ft_term(char **buff)
{
	char		c;
	int			rd;

	if ((*buff)[0] == 27 || (*buff)[0] < 0)
	{
		c = (*buff)[0];
		rd = (int)read(0, *buff, 7);
		(*buff)[rd] = '\0';
		ft_realloc_term(buff, c);
	}
}

static void		ft_prompt_mini(char **buff)
{
	count_and_erase_line((*g_global->cursor), g_global->first, 3);
	if (g_global->sig != 1)
		ft_info_line(*g_global->cursor, g_global->var);
	ft_read_list(g_global->first, (*g_global->cursor), 1);
	ft_bzero(*buff, 8);
}

static int		ft_free_and_quit(char **str, int i)
{
	ft_strdel(str);
	return (i);
}

int				ft_mini_loop(int *i, int *pos, char **cmd, char *buff)
{
	int			rd;
	int			a;

	while ((rd = (int)read(0, buff, 1)) > 0)
	{
		buff[rd] = '\0';
		ft_term(&buff);
		if (!(a = minihelp(&buff)))
			return (0);
		else if (a == 1)
			break ;
		if (ft_mini_want(buff, i, pos, cmd) == 0)
		{
			ft_add_realloc(cmd, buff[0], ++(*pos));
			ft_add_elem(g_global->list, buff[0], (*g_global->list)->next);
			(*g_global->list) = (*g_global->list)->next;
			(*i)++;
		}
		if (g_global->sig == 3 || g_global->sig == 2)
			return (ft_free_and_quit(&buff, 0));
		ft_prompt_mini(&buff);
	}
	return (ft_free_and_quit(&buff, 1));
}
