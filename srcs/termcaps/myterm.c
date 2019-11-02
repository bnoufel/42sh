/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myterm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:58 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:58 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			ft_is_emptyline(t_list *l)
{
	if (!l->next->next && !l->prev)
		return (1);
	return (0);
}

void		ft_free_all_jobs(void)
{
	t_job *tmp;

	while (g_jobs && g_jobs->prev)
		g_jobs = g_jobs->prev;
	while (g_jobs)
	{
		tmp = g_jobs;
		g_jobs = g_jobs->next;
		ft_free_all_processes(&tmp);
		ft_strdel(&(tmp->cmd));
		free(tmp);
		tmp = NULL;
	}
}

void		help_after(t_process *pro, int pdid, int *status)
{
	if (WEXITSTATUS(*status) == 22)
		kill(pro->pid, 30);
	else if (pdid != 0)
		ft_after_waitpid(status, pdid, pro->name, 1);
}
