/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:33:33 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:33:35 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				readheredoc(t_par *cur)
{
	char	*cmp;
	char	*hd;
	char	*tcp;
	int		i;
	int		c;

	if (!cur->next->lav && (g_global->sig = 1))
		return (1);
	(hd = ft_strdup(" ")) ? 0 : malloc_failed("readheredoc");
	i = 0;
	(cmp = ft_strjoin(cur->next->lav->av, "\n"))
	? 0 : malloc_failed("readheredoc");
	ft_mini_read(&hd, &i, 4, ' ');
	ft_cursorless();
	hd[0] ? hd[ft_strlen(hd) - 1] = '\n' : 0;
	(tcp = ft_strdup(hd + 1)) ? 0 : malloc_failed("readheredoc");
	ft_strdel(&hd);
	if (ft_strcmp(tcp, cmp))
		write(cur->fd[1], tcp, ft_strlen(tcp));
	pushfd(cur);
	c = ft_strcmp(tcp, cmp) ? 0 : 1;
	ft_strdel(&tcp);
	ft_strdel(&cmp);
	return (c);
}

static void		initread(int *r, t_av **av, char tmp[PATH_MAX], int *i)
{
	ft_bzero(tmp, sizeof(PATH_MAX));
	*r = 0;
	*av = *av ? (*av)->next : *av;
	while (*av && !ft_strcmp("-r", (*av)->av))
	{
		*r = 1;
		*av = (*av)->next;
	}
	*av && (*i = (int)ft_strlen((*av)->av)) < PATH_MAX - 4
	? ft_strcpy(tmp, (*av)->av) : 0;
	if (!(*av))
		*i = 0;
	tmp[(*i)++] = '=';
}

static	void	inread(t_var **var, char *tmp, int *i, t_av **av)
{
	if (tmp[*i - 1] == ' ' || tmp[*i - 1] == '\t')
	{
		*av && (*av)->next ? (tmp[*i - 1] = '\0') : 0;
		ft_list_nchange_if(var, tmp, &env_strequ, 0);
		if (*av && (*av)->next)
		{
			*av = (*av)->next;
			ft_bzero(tmp, sizeof(tmp));
			(*i = (int)ft_strlen((*av)->av)) < PATH_MAX - 4
			? ft_strcpy(tmp, (*av)->av) : 0;
			tmp[(*i)++] = '=';
		}
	}
}

static	void	afteread(t_av *av, int *i, t_var **var, char *tmp)
{
	if (av && av->next)
		av = av->next;
	else
		return ;
	while (av && av->next)
	{
		av = av->next;
		if (tmp[0])
		{
			(*i = (int)ft_strlen(av->av)) < PATH_MAX - 4
			? ft_strcpy(tmp, av->av) : 0;
			tmp[(*i)++] = '=';
			tmp[(*i)++] = '\0';
			ft_list_nchange_if(var, tmp, &env_strequ, 0);
		}
	}
}

int				readvar(t_par *cur, t_var **var, int fd, int fds[2])
{
	int		i;
	int		ret;
	char	tmp[PATH_MAX];
	int		r;
	t_av	*save;

	whichfd(cur, &fd, fds, &save);
	initread(&r, &(cur->lav), tmp, &i);
	while ((ret = read(fd, tmp + i, 1)) > 0 && i < PATH_MAX - 1)
	{
		if (g_global->sig)
		{
			ft_putstr("\x1b[1A");
			return (1);
		}
		(!r && tmp[i] == 92) ? (tmp[i] = '\0')
		: (tmp[++i] = '\0');
		inread(var, tmp, &i, &(cur->lav));
		if (tmp[i - 1] == '\n' && !(tmp[i - 1] = '\0')
		&& !ft_list_nchange_if(var, tmp, &env_strequ, 0))
			break ;
	}
	afteread(cur->lav, &i, var, tmp);
	cur->lav = save;
	return (0);
}
