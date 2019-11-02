/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freestructs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:37:49 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:37:50 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		freefds(void)
{
	t_fds *fds;
	t_fds *t;

	fds = g_global->fds;
	while (fds)
	{
		t = fds;
		fds = fds->next;
		free(t);
		t = NULL;
	}
	g_global->fds = NULL;
	close_fdmax();
}

bool		ft_free_tab(char **to_free)
{
	int i;

	i = 0;
	if (!to_free)
		return (false);
	while (to_free[i])
		ft_strdel(&(to_free[i++]));
	free(to_free);
	to_free = NULL;
	return (true);
}

void		malloc_failed(char *prog)
{
	ft_putstr_fd(prog, 2);
	ft_putendl_fd(" : has failed.", 2);
	if (g_global)
		ft_bye_bye(g_global->var, 0, NULL, 1);
	else
		exit(1);
}

void		free_struct_folder(t_split *ofolder)
{
	ft_strdel(&(ofolder->before));
	ft_strdel(&(ofolder->middle));
	ft_strdel(&(ofolder->after));
}
