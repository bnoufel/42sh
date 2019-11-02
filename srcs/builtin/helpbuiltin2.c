/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpbuiltin2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:32:54 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:44:47 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	whichfd(t_par *cur, int *fd, int fds[2], t_av **save)
{
	t_par	*bef;
	int		c;

	*save = cur->lav;
	c = 0;
	*fd = 0;
	if (cur->action[0] == '<')
		*fd = cur->fd[0];
	else if (cur->prev && (!ft_strcmp(cur->prev->action, "|")
	&& cur->action[0] != '<'))
	{
		bef = cur->prev;
		while (bef->prev && (bef->prev->action[0] == '<'
		|| bef->prev->action[0] == '>' || ft_isdigit(bef->prev->action[0])))
		{
			bef->prev->action[0] == '<' ? c = 1 : 0;
			bef = bef->prev;
		}
		*fd = c ? fds[0] : bef->fd[0];
	}
}

void	pathstat(int *c, char **mydir, char *av, struct stat *s)
{
	char	*cdp;

	cdp = NULL;
	*c = -1;
	if (av && !(*c = lstat(av, s)))
		giverealname(mydir, av);
	else if (av && retenv((*g_global->var)->lenv, "CDPATH"))
	{
		(cdp = ft_strdup(retenv((*g_global->var)->lenv, "CDPATH"))) ? 0
			: malloc_failed("pathstat");
		if ((cdp = cdpath(cdp, av))
				&& !(*c = lstat(cdp, s)))
		{
			giverealname(mydir, cdp);
			ft_strdel(&cdp);
		}
	}
}

void	nopaths(int opt[2], t_env *tmp, t_var **var)
{
	t_env *env;

	env = NULL;
	if (!opt[0])
	{
		(env = (t_env *)malloc(sizeof(t_env))) ? 0
			: malloc_failed("actualize_env");
		env->next = NULL;
		ft_strcpy(ft_strcpy(env->elem, "OLDPWD=") + 7, g_global->spwd->old_pwd);
		tmp ? (tmp->next = env)
			: ((*var)->lenv = tmp);
	}
	if (!opt[1])
	{
		(env = (t_env *)malloc(sizeof(t_env))) ? 0
			: malloc_failed("actualize_env");
		env->next = NULL;
		ft_strcpy(ft_strcpy(env->elem, "PWD=") + 4, g_global->spwd->pwd);
		tmp ? (tmp->next = env)
			: ((*var)->lenv = tmp);
	}
}
