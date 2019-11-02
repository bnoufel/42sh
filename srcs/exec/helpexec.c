/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 13:40:06 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/19 10:07:46 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		status(t_par *cur, int fd[2])
{
	if (cur && !cur->prev)
	{
		g_global->jobs = true;
		g_global->pipe = 0;
		pipensavemax(fd);
	}
	if (cur && cur->action[0] == '|' && !cur->action[1])
		g_global->pipe = 1;
	if (cur && ((g_global->ret && cur->prev && !ft_strcmp(cur->prev->action,
	"||")) || (!g_global->ret && cur->prev && !ft_strcmp(cur->prev->action,
	"&&")) || (!cur->prev || (ft_strcmp(cur->prev->action, "||")
	&& ft_strcmp(cur->prev->action, "&&")))))
		return (1);
	return (0);
}

int		nofork(t_par *cur)
{
	ft_strdel(&(g_global->cmdline));
	g_global->cmdline = cur->lav ? transform_list_to_char(cur->lav) : NULL;
	if (cur->lav && ft_strcmp(cur->lav->av, "env")
	&& ft_strcmp(cur->lav->av, "echo") && ft_strcmp(cur->action, "|"))
		return (1);
	return (0);
}

int		dofork(t_par *cur, int r)
{
	if (r > 1 || !ft_strcmp(cur->action, "|")
	|| (cur->lav && !ft_strcmp(cur->lav->av, "env"))
	|| (cur->lav && !ft_strcmp(cur->lav->av, "echo"))
	|| (cur->sub && cur->lav && cur->lav->av[0] == 40))
	{
		if (cur->sub && cur->lav && cur->lav->av[0] == 40)
			g_global->sub++;
		return (1);
	}
	return (0);
}

int		gonext(t_par **cur, char **tofree)
{
	char	*line;
	t_av	*iter;

	iter = *cur ? (*cur)->lav : 0;
	while (iter && iter->next)
		iter = iter->next;
	if (iter)
	{
		line = ft_strjoin("_=", iter->av);
		ft_strlen(iter->av) < PATH_MAX - 3
		? ft_list_nchange_if(g_global->var, line, &env_strequ, 1) : 0;
		ft_strdel(&line);
	}
	ft_strdel(tofree);
	while (*cur && ((*cur)->action[0] == '>' || (*cur)->action[0] == '<'
	|| ft_isdigit((*cur)->action[0])))
		*cur = (*cur)->next;
	if ((*cur) && (*cur = (*cur)->next))
		return (1);
	return (0);
}
