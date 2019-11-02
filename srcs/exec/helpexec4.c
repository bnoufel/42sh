/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpexec4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:07:52 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:07:54 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ckfav(t_par **cur, int i)
{
	char	*t;
	char	gch[PATH_MAX];

	t = (*cur)->av[0];
	while (t[i])
	{
		if (i && t[i] == '/' && t[0] != '/')
		{
			ft_strlen((*cur)->av[0]) < PATH_MAX ? ft_strcpy(gch, (*cur)->av[0])
			: ft_bzero(gch, sizeof(PATH_MAX));
			if (ft_strlen((*cur)->av[0]) > 2 && ft_strequ((*cur)->av[0], "./"))
			{
				t = ft_strjoin(getcwd(gch, sizeof(gch)), (*cur)->av[0] + 1);
				ft_strdel(&(*cur)->av[0]);
				(*cur)->av[0] = t;
				return (1);
			}
			t = ft_strjoin(getcwd(gch, sizeof(gch)), (*cur)->av[0]);
			ft_strdel(&(*cur)->av[0]);
			(*cur)->av[0] = t;
			return (0);
		}
		i++;
	}
	return (0);
}

int		filllav(t_av **keep, t_par **topar, t_par **cur, t_av **tmp)
{
	int	i;

	i = 0;
	*tmp = NULL;
	while ((*cur)->av[i])
	{
		(*keep = (t_av *)malloc(sizeof(t_av)))
		&& ((*keep)->av = ft_strdup((*cur)->av[i]))
		? 0 : malloc_failed("hashkey");
		!i ? ((*topar)->lav->last->next = *keep) : 0;
		(*tmp) ? (*tmp)->next = *keep : 0;
		*tmp = *keep;
		(*keep)->next = NULL;
		*keep = (*keep)->next;
		i++;
	}
	ft_free_tab((*cur)->av);
	buildtabav(topar, (*cur)->ac + 1);
	(*cur)->av = (*topar)->av;
	ft_plist_clear(topar);
	return (0);
}

int		execf(t_var **var, t_par *cur)
{
	char	*u;

	if (cur && cur->lav)
	{
		if (*var && (*var)->fnc && retenv((*var)->fnc, cur->lav->av))
		{
			(u = ft_strjoin(retenv((*var)->fnc, cur->lav->av), " ")) ? 0
				: malloc_failed("execf");
			g_global->ret = eval(&u, var);
			return (1);
		}
	}
	return (0);
}

int		fncheck(t_var **var, t_par *cur)
{
	char	t[PATH_MAX];
	int		i;
	char	u[PATH_MAX];

	i = 0;
	ft_bzero(t, sizeof(PATH_MAX));
	ft_bzero(u, sizeof(PATH_MAX));
	cur && cur->lav && ft_strlen(cur->lav->av) < PATH_MAX
		? ft_strcpy(t, cur->lav->av) : 0;
	while (t[i])
	{
		if (t[i] == '(' && t[i + 1] == ')')
		{
			u[i] = '\0';
			i += 2;
			if (t[i] == '{')
				t[i] = ' ';
			if (t[ft_strlen(t) - 1] == '}')
				t[ft_strlen(t) - 1] = ' ';
			return (add_fnc(var, u, t, i));
		}
		u[i] = t[i];
		i++;
	}
	return (1);
}

int		noshellbang(t_par **cur, t_par **topar, int i)
{
	t_av		*keep;
	t_av		*tmp;
	char		*path;

	if (!(tmp = NULL) && !ft_strcmp((*cur)->lav->av, "./42sh"))
		return (0);
	(path = ft_strdup("/bin/sh ")) ? 0 : malloc_failed("noshellbang");
	parseline(&path, topar);
	ft_strdel(&path);
	while ((*cur)->av[i])
	{
		(keep = (t_av *)malloc(sizeof(t_av))) ? 0 : malloc_failed("hashkey");
		(keep->av = ft_strdup((*cur)->av[i])) ? 0 : malloc_failed("hashkey");
		!i ? ((*topar)->lav->last->next = keep) : 0;
		tmp ? tmp->next = keep : 0;
		tmp = keep;
		keep->next = NULL;
		keep = keep->next;
		i++;
	}
	ft_free_tab((*cur)->av);
	buildtabav(topar, (*cur)->ac + 1);
	(*cur)->av = (*topar)->av;
	ft_plist_clear(topar);
	return (0);
}
