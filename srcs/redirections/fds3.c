/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 16:34:27 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 16:00:38 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				openerror(t_par *cur)
{
	if (access(cur->next->lav->av, F_OK))
	{
		write(2, "mysh: ", 6);
		write(2, cur->next->lav->av, ft_strlen(cur->next->lav->av));
		write(2, ": No such file or directory\n", 28);
	}
	else
	{
		write(2, "mysh: ", 6);
		write(2, cur->next->lav->av, ft_strlen(cur->next->lav->av));
		write(2, ": permission denied\n", 20);
	}
	return (1);
}

static int		aggreg2(t_par *cur, int c)
{
	if (sisdigit(cur->next->lav->av) && ((cur->action[0] == '<'
	&& dup2(ft_atoc(cur->next->lav->av, &c), STDIN_FILENO) != -1)
	|| (cur->action[0] == '>' && dup2(ft_atoc(cur->next->lav->av, &c),
	STDOUT_FILENO) != -1)))
		g_global->fdmax < ft_atoc(cur->next->lav->av, &c)
		? (g_global->fdmax = ft_atoc(cur->next->lav->av, &c)) : 0;
	else if (!ft_strcmp(cur->next->lav->av, "-") && ((cur->action[0] == '<'
	&& close(STDIN_FILENO) != -1) || (cur->action[0] == '>'
	&& close(STDOUT_FILENO) != -1)))
		;
	else if (cur->action[ft_strlen(cur->action) - 2] == '<'
	&& !sisdigit(cur->next->lav->av) && ft_strcmp(cur->next->lav->av, "-"))
		ft_isdigit(cur->action[0]) ? dup2(ft_atoc(cur->action, &c), cur->fd[0])
		: dup2(cur->fd[0], STDIN_FILENO);
	else if (cur->action[ft_strlen(cur->action) - 2] == '>'
	&& !sisdigit(cur->next->lav->av) && ft_strcmp(cur->next->lav->av, "-"))
		ft_isdigit(cur->action[0]) ? dup2(cur->fd[1], ft_atoc(cur->action, &c))
		: dup2(cur->fd[1], STDOUT_FILENO);
	else
		return (1);
	return (0);
}

int				helpaggreg(t_par *cur, int c)
{
	if (!ft_strcmp(cur->next->action, "|")
	&& !ft_strcmp(cur->next->lav->av, "1")
	&& cur->action[ft_strlen(cur->action) - 2] == '>')
	{
		if (ft_isdigit(cur->action[0]) && dup2(cur->fd[1],
		ft_atoc(cur->action, &c)) != -1)
			g_global->fdmax < ft_atoc(cur->action, &c)
			? (g_global->fdmax = ft_atoc(cur->action, &c)) : 0;
	}
	else if (ft_isdigit(cur->action[0]) && sisdigit(cur->next->lav->av)
	&& dup2(ft_atoc(cur->next->lav->av, &c), ft_atoc(cur->action, &c)) != -1)
		g_global->fdmax < ft_atoc(cur->next->lav->av, &c)
		? (g_global->fdmax = ft_atoc(cur->next->lav->av, &c)) : 0;
	else if (ft_isdigit(cur->action[0]) && !ft_strcmp(cur->next->lav->av, "-"))
		close(ft_atoc(cur->action, &c));
	else
		return (aggreg2(cur, c));
	return (0);
}

void			initdup(t_par *cur, int fd[2])
{
	t_par	*bef;
	int		c;

	c = 0;
	if (cur->prev && (!ft_strcmp(cur->prev->action, "|")
	&& cur->action[0] != '<'))
	{
		bef = cur->prev;
		while (bef->prev && (bef->prev->action[0] == '<'
		|| bef->prev->action[0] == '>' || ft_isdigit(bef->prev->action[0])))
		{
			bef->prev->action[0] == '<' ? c = 1 : 0;
			bef = bef->prev;
		}
		c ? dup2(fd[0], STDIN_FILENO) : dup2(bef->fd[0], STDIN_FILENO);
	}
}

int				writeonfile(t_par *cur, int c)
{
	if (notthisone(cur))
		return (0);
	if (!cur || !cur->fd[1] || !cur->next || !cur->next->lav)
		return (1);
	close(cur->fd[1]);
	cur->fd[1] = c == 1
	? open(cur->next->lav->av, O_WRONLY | O_TRUNC
	| O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH)
	: open(cur->next->lav->av, O_WRONLY | O_APPEND
	| O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	pushfd(cur);
	if (cur->fd[1] == -1)
	{
		write(2, "mysh failed to write on ", 24);
		write(2, cur->next->lav->av, ft_strlen(cur->next->lav->av));
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}
