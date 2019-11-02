/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:31:52 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/19 13:36:57 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static	int		display_echo(t_av *av)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	av = av->next;
	if (!av)
		write(1, "\n", 1);
	while (av && !ft_strcmp(av->av, "-n"))
	{
		av = av->next;
		j = 1;
	}
	while (av)
	{
		av->av[0] ? ft_putstr(av->av) : 0;
		av->av[0] && av->next ? ft_putstr(" ") : 0;
		av = av->next;
		if (!av)
			!j ? write(1, "\n", 1) : ft_putstr("\033[47;30m%\033[0m\n");
	}
	return (0);
}

static int		export(t_par *par, t_var **var)
{
	int		a;
	t_av	*save;

	a = 0;
	save = par ? par->lav : NULL;
	par->lav = par ? par->lav->next : NULL;
	while (par && par->lav
	&& onebyone(&(par->lav->av), *var, 0, 0)
	&& !ft_strcmp(par->lav->av, "-p"))
		par->lav = par->lav->next;
	if (!par->lav)
		return (display_export(var, &par, &save));
	while (par->lav && onebyone(&(par->lav->av), *var, 0, 0)
	&& (a = check_if_fnc(par->lav->av, var, 0)))
	{
		par->lav = par->lav->next;
		if (a && (par->lav = save))
			return (1);
	}
	par->lav = save;
	return (0);
}

static	int		built2(t_par *cur, t_var **var)
{
	if (cur && cur->lav && !ft_strcmp(cur->lav->av, "unsetenv"))
		return (unsetenvv(cur, &((*var)->lenv)));
	else if (cur && cur->lav && (!ft_strcmp(cur->lav->av, "env")))
		return (wtdwenv(cur, var));
	else if (cur && cur->lav && !ft_strcmp(cur->lav->av, "echo"))
		return (display_echo(cur->lav));
	else if (cur && cur->lav && !ft_strcmp(cur->lav->av, "unset"))
		return (unset(cur, var));
	else if (cur && cur->lav && !ft_strcmp(cur->lav->av, "exit"))
		return (ft_bye_bye(var, 0, NULL, 0));
	else if (cur && cur->lav && !ft_strcmp(cur->lav->av, "history"))
		return (ft_history());
	else if (cur && cur->lav && !ft_strcmp(cur->lav->av, "infosh"))
		return (ft_display_esc());
	else if (cur && cur->lav && !ft_strcmp(cur->lav->av, "fg"))
		return (ft_fg(cur->lav));
	else if (cur && cur->lav && !ft_strcmp(cur->lav->av, "bg"))
		return (ft_fg(cur->lav));
	else if (cur && cur->lav && !ft_strcmp(cur->lav->av, "jobs"))
		return (display_jobs());
	else if (cur && cur->lav && !ft_strcmp(cur->lav->av, "reload")
	&& create_tab((*var)->lenv))
		return (0);
	return (2);
}

int				builtin_command(t_par **par, t_var **var, int fds[2])
{
	t_par			*cur;

	cur = *par;
	if (cur && cur->lav && !ft_strcmp(cur->lav->av, "cd"))
	{
		if (!(*var)->lenv->elem[0])
			return (1);
		return (handle_dirissue(cur->ac, cur->lav, *var));
	}
	if (cur && cur->lav && !ft_strcmp(cur->lav->av, "read"))
		return (readvar(cur, var, 0, fds));
	else if (cur && cur->lav && !ft_strcmp(cur->lav->av, "export"))
		return (export(cur, var));
	else if (cur && cur->lav && !ft_strcmp(cur->lav->av, "setenv"))
		return (setnewenv(cur->ac, cur->lav, &((*var)->lenv), 0));
	return (built2(cur, var));
}
