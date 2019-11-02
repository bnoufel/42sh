/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:33 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:34 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static	int		startwdigit(t_par *cur)
{
	int i;
	int c;

	c = 0;
	i = 0;
	if (!((i = chkredir(cur->action))) && helpaggreg(cur, c))
	{
		ft_putendl_fd("mysh: Bad file descriptor", 2);
		return (1);
	}
	else if (i == 1)
		dup2(cur->fd[1], ft_atoc(cur->action, &c));
	else if (i == 2)
		dup2(ft_atoc(cur->action, &c), cur->fd[0]);
	g_global->fdmax < ft_atoc(cur->action, &c)
	? (g_global->fdmax = ft_atoc(cur->action, &c)) : 0;
	return (0);
}

int				dealwfds1(t_par *cur, int fd[2])
{
	t_par	*start;

	start = cur;
	initdup(cur, fd);
	while (cur && (cur->action[0] == '<' || cur->action[0] == '>'
	|| ft_isdigit(cur->action[0])))
	{
		if (!ft_isdigit(cur->action[0]) && cur->action[1] == '<')
			dup2(cur->fd[0], STDIN_FILENO);
		else if (cur->action[0] == '<' && !cur->action[1])
			dup2(cur->fd[0], STDIN_FILENO);
		else if (cur->action[0] == '>' && (!cur->action[1]
		|| cur->action[1] == '>'))
			dup2(cur->fd[1], STDOUT_FILENO);
		else if (startwdigit(cur))
			return (1);
		cur = cur->next;
	}
	return (0);
}
