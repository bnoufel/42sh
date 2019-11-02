/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:33:03 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:33:04 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		display_env(t_env *env)
{
	while (env && env->elem[0])
	{
		write(1, env->elem, ft_strlen(env->elem));
		write(1, "\n", 1);
		env = env->next;
	}
	return (0);
}

int		checkvarname(char *s)
{
	int i;

	i = 1;
	if (s[0] != '_' && !ft_isalpha(s[0]))
	{
		ft_putstr("mysh: invalid variable name\n");
		return (1);
	}
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
		{
			ft_putstr("mysh: invalid variable name\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int		helpchkivar(int f, int h, t_var **var, char *s)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	if (!ckvar(ft_strdup(s)))
		return (0);
	h = g_global->env ? 1 : h;
	f = g_global->env ? 0 : f;
	while (s && s[i])
	{
		if (s[i] == '=' && s[i + 1] != '=')
		{
			c = 1;
			!f ? ft_list_nchange_if(var, s, &env_strequ, h) : 0;
			break ;
		}
		i++;
	}
	return (c && s[0] ? 1 : 0);
}

void	giverealname(char **mydir, char *av)
{
	char temp[PATH_MAX];

	if (av[0] == '/')
	{
		(*mydir = ft_strdup(av)) ? 0 : malloc_failed("giverealname");
		startfromroot(mydir);
	}
	else
	{
		ft_strcpy(temp, g_global->spwd->pwd);
		temp[0] && temp[ft_strlen(temp) - 1] != '/' ? ft_strcat(temp, "/") : 0;
		ft_strcat(temp, av);
		(*mydir = ft_strdup(temp)) ? 0 : malloc_failed("giverealname");
		handledots(mydir, 0, 0, ft_strlen(*mydir));
	}
}

int		wr(int r, char **cp, int *a)
{
	char *t;

	r = r ? 1 : 0;
	t = lltoa(r);
	*cp = substitute(*cp, t);
	*a = (int)ft_strlen(*cp);
	return (1);
}
