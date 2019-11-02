/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpterm2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:53 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:54 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		ft_free_histo(void)
{
	t_history	*tmp;
	t_list		*tmp2;
	t_list		*tmp3;

	if (!(*g_global->cursor)->history)
		return ;
	while ((*g_global->cursor)->history->prev)
		(*g_global->cursor)->history = (*g_global->cursor)->history->prev;
	while ((*g_global->cursor)->history)
	{
		tmp = (*g_global->cursor)->history;
		tmp2 = tmp->list;
		while (tmp2)
		{
			tmp3 = tmp2;
			tmp2 = tmp2->next;
			free(tmp3);
			tmp3 = NULL;
		}
		(*g_global->cursor)->history = (*g_global->cursor)->history->next;
		free(tmp);
		tmp = NULL;
		free(tmp2);
		tmp2 = NULL;
	}
}

void		ft_free_cccv(void)
{
	t_list	*tmp2;
	t_list	*tmp3;

	if ((*g_global->cursor)->save)
	{
		tmp2 = (*g_global->cursor)->save;
		while (tmp2->prev)
			tmp2 = tmp2->prev;
		while (tmp2)
		{
			tmp3 = tmp2;
			tmp2 = tmp2->next;
			free(tmp3);
		}
		free(tmp2);
	}
}

void		ft_free_edition(void)
{
	t_list	*tmp2;

	while ((*g_global->list)->prev)
		*g_global->list = (*g_global->list)->prev;
	while (*g_global->list)
	{
		tmp2 = *g_global->list;
		*g_global->list = (*g_global->list)->next;
		free(tmp2);
	}
}

void		ft_free_cursor(t_var **var, char **buff)
{
	t_pid	*tmp4;

	ft_strdel(buff);
	(void)buff;
	free(g_global->spwd);
	g_global->spwd = NULL;
	clean_tab();
	clean_bin();
	ft_free_histo();
	ft_free_cccv();
	free((*g_global->cursor)->old);
	free((*g_global->cursor));
	freevar(*var);
	while (g_global->pid)
	{
		tmp4 = g_global->pid;
		g_global->pid = g_global->pid->next;
		free(tmp4);
		tmp4 = NULL;
	}
	if (!(!g_global->list || !*g_global->list || (!g_global->first)))
		ft_free_edition();
	free(g_global);
}

void		ft_free_pgid(void)
{
	t_pgid *tmp;

	while (g_pgid->prev)
		g_pgid = g_pgid->prev;
	while (g_pgid)
	{
		tmp = g_pgid;
		g_pgid = g_pgid->next;
		free(tmp);
	}
}
