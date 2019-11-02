/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:30 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:20 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			chkredir(char *s)
{
	int a;
	int i;

	i = 0;
	a = 0;
	while (s && s[i])
	{
		if (s[i] == '>')
			a = 1;
		if (s[i + 1] == '>' && a == 1)
		{
			i++;
			a = 3;
		}
		else if (s[i] == '<')
			a = 2;
		else if (s[i] == '&' && s[i + 1] != '>' && s[i + 1] != '<')
			return (0);
		i++;
	}
	return (a);
}

void		transferavs(t_par **par, t_par **cur, int c, t_var *var)
{
	t_av			*tr;

	if (c || !(*par))
		return ;
	rewriteavs(cur, var, 0, 0);
	tr = *cur && (*cur)->lav ? (*cur)->lav : NULL;
	tr = tr ? tr->next : 0;
	while (tr)
	{
		newav(*par, tr->av, ft_strlen(tr->av), 0);
		tr = tr->next;
	}
}

int			openfile(t_par *cur)
{
	int c;

	c = 0;
	if (notthisone(cur))
		return (0);
	if (!cur || !cur->fd[0] || !cur->next || !cur->next->lav)
		return (1);
	if (!access(cur->next->lav->av, F_OK) && !access(cur->next->lav->av, R_OK))
	{
		close(cur->fd[0]);
		cur->fd[0] = open(cur->next->lav->av, O_RDONLY);
		if (ft_isdigit(cur->action[0])
		&& dup2(cur->fd[0], ft_atoc(cur->action, &c)) == -1)
		{
			ft_putendl_fd("mysh: Bad file descriptor", 2);
			return (1);
		}
		pushfd(cur);
		return (0);
	}
	return (openerror(cur));
}

int			createfds(t_par *cur, t_var *var, int c, int d)
{
	t_par	*save;

	save = NULL;
	while (ft_isdigit(cur->action[0]) || !ft_strcmp(cur->action, "|")
	|| cur->action[0] == '<' || cur->action[0] == '>')
	{
		c = !c && ft_strcmp(cur->action, "|")
		&& (save = cur) ? 1 : c;
		if ((((cur->action[0] == '>' && (!cur->action[1]
		|| (cur->action[1] != '>' && cur->next && (!cur->next->lav
		|| (ft_strcmp(cur->next->lav->av, "-")
		&& !sisdigit(cur->next->lav->av)))))) || (ft_isdigit(cur->action[0])
		&& chkredir(cur->action) == 1)) && writeonfile(cur, 1))
		|| (((cur->action[0] == '>' && cur->action[1] == '>')
		|| (ft_isdigit(cur->action[0]) && chkredir(cur->action) == 3))
		&& writeonfile(cur, 2)) || (!ft_isdigit(cur->action[0])
		&& cur->action[1] == '<' && heredoc(cur)) || (((cur->action[0] == '<'
		&& !cur->action[1]) || (ft_isdigit(cur->action[0])
		&& chkredir(cur->action) == 2)) && openfile(cur)))
			return (1);
		d = !d && !ft_strcmp(cur->action, "|") ? 1 : d;
		transferavs(&save, &(cur->next), d, var);
		cur = cur->next;
	}
	return (0);
}

int			heredoc(t_par *cur)
{
	if (notthisone(cur))
		return (0);
	while (!readheredoc(cur) && !g_global->sig)
		;
	if (g_global->sig == 1)
		return (1);
	g_global->sig = 0;
	return (0);
}
