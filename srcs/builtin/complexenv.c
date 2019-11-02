/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complexenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:32:00 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:32:03 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int		shlvl(t_env **env, t_var *var)
{
	int		i;
	t_env	*cur;

	i = 6;
	cur = *env;
	while (cur->elem[i])
	{
		if (!ft_isdigit(cur->elem[i]))
		{
			cur->elem[6] = '1';
			cur->elem[7] = '\0';
			return (1);
		}
		i++;
	}
	helpinvar(cur->elem + 6, '+', var, NULL);
	return (1);
}

t_env			*copyenv(char **environ, t_var *var, int c, int d)
{
	int		a;
	t_env	*tmp;
	t_env	*env;
	t_env	*head;

	tmp = NULL;
	head = NULL;
	a = -1;
	while (environ[++a] != 0)
	{
		if (!(env = (t_env *)malloc(sizeof(t_env))))
			malloc_failed("copyenv");
		env->next = NULL;
		!a ? head = env : 0;
		tmp ? tmp->next = env : 0;
		ft_strcpy(env->elem, environ[a]);
		env_strequ(env->elem, "SHLVL") && shlvl(&env, var) ? (c = 1) : 0;
		env_strequ(env->elem, "PWD") ? (d = 1) : 0;
		env_strequ(env->elem, "PATH") ? create_tab(env) : 0;
		tmp = env;
		env = env->next;
	}
	!d ? nopwdcase(&tmp, &head, a++) : 0;
	!c ? noshlvlcase(&tmp, &head, a) : 0;
	return (head);
}

t_av			*checkifvar(t_par *cur, t_var **var, int j, int f)
{
	t_av		*av;
	char		*t;

	av = cur->lav;
	f = !f ? 1 : 0;
	while (cur && av && ((av->av[0] != 34 && av->av[0] != 39) || g_global->env))
	{
		if (g_global->env)
		{
			onebyone(&(av->av), *var, 0, 0);
			t = bckslshav(av->av, chardelim(av->av));
			ft_strdel(&(av->av));
			av->av = t;
		}
		j ? (j = 0) : 0;
		if (!ft_strcmp(av->av, "env"))
			return (f && !g_global->env ? checkifvar(cur, var, j, f) : av);
		if (ft_strlen(av->av) < PATH_MAX && !helpchkivar(f, j, var, av->av))
			return (av);
		av = av->next;
	}
	return (f && !g_global->env ? checkifvar(cur, var, j, f) : av);
}

static int		envend(t_av **save, t_par **par, t_var **var)
{
	if ((*par)->lav && !ft_strcmp((*par)->lav->av, "env"))
		return (wtdwenv(*par, var));
	if ((*par)->lav)
		return (2);
	(*par)->lav = *save;
	return (display_env((*var)->lenv));
}

int				wtdwenv(t_par *par, t_var **var)
{
	int		i;
	t_av	*save;

	i = 1;
	save = par ? par->lav : NULL;
	while (par && par->lav && onebyone(&(par->lav->av), *var, 0, 0)
	&& (!ft_strcmp(par->lav->av, "-i") || (!ft_strcmp(par->lav->av, "env"))))
	{
		(!ft_strcmp(par->lav->av, "-i") && (*var)->lenv)
		? ft_list_clear(&((*var)->lenv)) : 0;
		par->lav = par->lav->next;
	}
	if (par->lav && par->lav->av[0] == '-' && par->lav->av[1] != 'i')
	{
		write(2, "usage: env [-i] [name+value ...]", 32);
		write(2, " [utility [argument ...]]\n", 26);
		return (1);
	}
	g_global->env = 1;
	par->lav = checkifvar(par, var, i, 0);
	g_global->env = 0;
	(*var)->tenv = adaptarray(var);
	return (envend(&save, &par, var));
}
