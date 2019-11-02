/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:32:18 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:32:19 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		actualize_env(t_var **var)
{
	t_env	*env;
	t_env	*tmp;
	int		opt[2];

	opt[0] = 0;
	opt[1] = 0;
	tmp = NULL;
	env = (*var)->lenv;
	while (env)
	{
		if (env_strequ(env->elem, "OLDPWD") && (opt[0] = 1))
			ft_strcpy((env->elem + 7), g_global->spwd->old_pwd);
		if (env_strequ(env->elem, "PWD") && (opt[1] = 1))
			ft_strcpy((env->elem + 4), g_global->spwd->pwd);
		tmp = env;
		env = env->next;
	}
	nopaths(opt, tmp, var);
	(*var)->tenv = adaptarray(var);
}

static int	setopt(char *s)
{
	int i;

	i = 1;
	while (s[i])
	{
		if (s[i] == 's')
			g_global->spwd->s = 1;
		else if (s[i] == 'P')
			g_global->spwd->p = 1;
		else if (s[i] == 'L')
			;
		else
		{
			write(2, "cd: no such file or directory: ", 31);
			write(2, s, ft_strlen(s));
			write(2, "\n", 1);
			return (0);
		}
		i++;
	}
	return (1);
}

int			checkav(t_av **av)
{
	int i;

	i = 1;
	g_global->spwd->p = 0;
	g_global->spwd->s = 0;
	(*av) = (*av)->next;
	while (*av)
	{
		if ((*av)->av[0] != '-')
			return (i);
		if ((*av)->av[0] == '-')
		{
			if (!(*av)->av[1] || (*av)->av[1] == '/')
				return (i);
			else if (!(setopt((*av)->av)))
				return (0);
		}
		*av = (*av)->next;
		i++;
	}
	return (i);
}

static	int	bopt(char *mydir, t_var *var)
{
	char	getcwdhappy[PATH_MAX];
	int		c;

	ft_strlen(mydir) < PATH_MAX ? ft_strcpy(getcwdhappy, mydir)
	: ft_bzero(getcwdhappy, sizeof(PATH_MAX));
	if (!(c = chdir(mydir)))
	{
		ft_strcpy(g_global->spwd->old_pwd, g_global->spwd->pwd);
		if (getcwd(getcwdhappy, sizeof(getcwdhappy)) && (g_global->spwd->p
		|| !checkifpreviouslnk(g_global->spwd->pwd)))
			ft_strcpy(g_global->spwd->pwd,
			getcwd(getcwdhappy, sizeof(getcwdhappy)));
		else if (mydir[0] == '/')
			ft_strcpy(g_global->spwd->pwd, mydir);
		else
			ft_strcat(ft_strcat(g_global->spwd->pwd, "/"), mydir);
		actualize_env(&var);
	}
	ft_strdel(&mydir);
	return (!c ? 0 : 1);
}

int			dealwopt(char *av, t_var *var)
{
	struct stat s;
	int			c;
	char		*mydir;

	mydir = NULL;
	pathstat(&c, &mydir, av, &s);
	if (c || (g_global->spwd->s && (S_ISLNK(s.st_mode)
	|| checkifpreviouslnk(mydir)))
	|| (!S_ISLNK(s.st_mode) && !S_ISDIR(s.st_mode)))
	{
		ft_putstr_fd("cd: no such directory: ", 2);
		av && av[0] ? ft_putendl_fd(av, 2) : 0;
		ft_strdel(&mydir);
		return (1);
	}
	else if (!g_global->spwd->p && (S_ISLNK(s.st_mode)
	|| checkifpreviouslnk(mydir)) && !(c = chdir(mydir)))
	{
		ft_strcpy(g_global->spwd->old_pwd, g_global->spwd->pwd);
		ft_strcpy(g_global->spwd->pwd, mydir);
		actualize_env(&var);
		ft_strdel(&mydir);
		return (0);
	}
	return (c ? 1 : bopt(mydir, var));
}
