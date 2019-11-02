/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpterm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:52 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:53 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	wiwantvar(char *buff, t_cursor **c, t_list **l, t_var **var)
{
	if (buff[0] == '\n' && (*c)->search == 1)
		return (1);
	if (buff[0] == '\t')
	{
		if ((*c)->search == 1)
			return (1);
		ft_auto_completion(l, *c, var);
		return (1);
	}
	else if (buff[0] == 18 && buff[1] == 0)
		(*c)->search = 1;
	else if (buff[0] == 27 && buff[1] == 0)
		return (1);
	else if (buff[0] == 4 && buff[1] == 0)
	{
		if (!ft_is_emptyline(g_global->first))
		{
			((*l)->next->next) ? ft_free_right_node(l) : 0;
			return (1);
		}
		ft_bye_bye(var, 1, &buff, 0);
	}
	else
		return (3);
	return (2);
}

static int	wiwantfirst(char *buff, t_list **l, t_cursor **c, t_list *first)
{
	if (buff[5] == 67)
		ft_right_word(l, " [C", *c, first);
	else if (buff[5] == 68)
		ft_left_word(l, " [D", *c, first);
	else if (left_down_right_up(buff, l, *c, first) != 0)
	{
		if ((*c)->is_selected == 1)
			ft_reset_selection(l);
		(*c)->is_selected = 0;
	}
	else if (ft_strcmp(buff + 1, "[18;2~") == 0)
		(*c)->color = ((*c)->color + 1) % 7;
	else if (buff[0] == 0x7f && buff[1] == '\0')
		ft_free_left_node(l);
	else if (buff[0] == 27 && buff[2] == '3')
		ft_free_right_node(l);
	else if (ft_home_end(l, buff) != 0)
		;
	else if (((*c)->search != 1) && (buff[0] <= 27 || buff[0] == 127))
		ft_option(buff, l, *c, first);
	else if (ft_strlen(buff) == 1)
		return (0);
	return (1);
}

int			ft_bye_bye(t_var **var, int n, char **buff, int r)
{
	if (!g_global)
		exit(r);
	if (!g_global->cursor || !*g_global->cursor)
		exit(r);
	ft_free_all_jobs();
	(*g_global->cursor)->col = 1;
	free(g_global->cmdline);
	if (g_global->is_scrpt != 1 && g_global->stdi != 1)
	{
		count_and_erase_line(*g_global->cursor, g_global->first, 3);
		if (tcsetattr(0, TCSANOW, (*g_global->cursor)->old) == -1)
			exit(r);
		ft_close(*g_global->cursor);
		freefds();
		ft_free_cursor(var, buff);
		if (g_pgid)
		{
			tcsetpgrp(0, g_pgid->old_pgid);
			ft_free_pgid();
		}
	}
	ft_putstr_fd("\x1b[?25h", 0);
	n == 1 ? ft_putendl("$> exit") : 0;
	exit((r) ? 1 : 0);
}

int			ft_is_what_i_want(char *buff, t_list **l, t_cursor *c, t_var **var)
{
	t_list	*first;
	int		a;

	first = g_global->first;
	if (buff[0] == 12 && buff[1] == 0)
	{
		ft_putstr("\x1b[2J");
		ft_putstr("\x1b[1;1H");
		return (1);
	}
	else if ((a = wiwantvar(buff, &c, l, var)) == 1)
		return (1);
	else if (!a)
		return (0);
	else if (a == 3 && buff[0] == '\n' && g_global->sig != 1)
		ft_enter(l, c, first, var);
	else if (a == 3 && buff[0] == 18 && buff[1] == 0)
		c->search = 1;
	else if (a == 3 && buff[0] == 27 && buff[1] == 0)
		return (1);
	else if (a == 3 && !wiwantfirst(buff, l, &c, first))
		return (0);
	c->completion = 0;
	return (1);
}
