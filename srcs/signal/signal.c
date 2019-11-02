/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:40:15 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:40:16 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void			ft_sigint(void)
{
	g_global->sig = 1;
	if (g_global->is_scrpt == 1)
		exit(0);
	g_global->prefix = 0;
	while ((*g_global->list)->prev)
		(*g_global->list) = (*g_global->list)->prev;
	while ((*g_global->list) && (*g_global->list)->next
	&& (*g_global->list)->next->next)
		ft_free_right_node(g_global->list);
	ft_putstr_fd("\n\n", 0);
	g_global->sear = 0;
	g_global->ret = -1;
	(*g_global->cursor)->job = 0;
	ioctl(0, TIOCSTI, "\n");
	if (!g_pgid)
		return ;
	while (g_pgid->next)
		g_pgid = g_pgid->next;
	g_global->is_scrpt ? tcsetpgrp(g_global->f_fd, g_pgid->new_pgid)
	: tcsetpgrp(0, g_pgid->new_pgid);
}

static void			ft_sigwinch(void)
{
	ft_ioctl(*g_global->cursor);
	ft_plu(*g_global->cursor, g_global->var);
	ft_putstr("\x1b[2J");
	ft_putstr("\x1b[1;1H");
	ft_info_line(*g_global->cursor, g_global->var);
	ft_read_list(g_global->first, *g_global->cursor, 1);
}

void				sig_h(int n)
{
	if (n)
		;
	exit(1);
}

void				ft_catch_sig(int n)
{
	if (n == SIGINT && checkpid())
		ft_sigint();
	if (n == SIGWINCH)
		ft_sigwinch();
}

void				set_signal_main(void)
{
	int i;

	i = 0;
	while (++i < 32)
	{
		if (i == 3 || i == 2 || i == 18 || i == 22)
			signal(i, SIG_IGN);
		else
			signal(i, SIG_DFL);
	}
}
