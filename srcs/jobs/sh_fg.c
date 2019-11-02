/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:08:42 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:08:44 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int		ft_fg_parse(t_av *av, int bg)
{
	if (!av->next)
		return (0);
	if (av->next->next || av->next->av[0] != '%'
	|| !is_only_numerical(av->next->av))
	{
		if (bg == 0)
			ft_putendl_fd("usage : fg %n", 2);
		else
			ft_putendl_fd("usage : bg %n", 2);
		return (1);
	}
	return (0);
}

static int		ft_find_job(char *str, int bg)
{
	int		n;
	t_job	*job;

	job = g_jobs;
	n = ft_atoi(str);
	if (n == 0)
		return (1);
	while (job->next && n > 0)
	{
		job = job->next;
		n--;
	}
	if (job->pgid == -1)
		return (1);
	if (n == 0)
		ft_wake_up(&job, bg);
	else
		return (1);
	return (0);
}

static int		ft_display_error(int bg)
{
	if (bg == 0)
		ft_putendl_fd("fg : no current job", 2);
	else
		ft_putendl_fd("bg : no current job", 2);
	return (1);
}

static int		ft_display_error2(int bg, t_av *av)
{
	if (bg == 0)
		ft_putstr_fd("fg : ", 2);
	else
		ft_putstr_fd("bg : ", 2);
	ft_putstr_fd(av->next->av, 2);
	ft_putendl_fd(": no such job", 2);
	return (1);
}

int				ft_fg(t_av *av)
{
	t_job	*job;
	int		bg;

	bg = ft_strcmp(av->av, "fg");
	if (!g_jobs)
		return (1);
	ft_rewind();
	job = g_jobs;
	if (ft_fg_parse(av, bg))
		return (1);
	if (av && !av->next)
	{
		while (job->next)
			job = job->next;
		if (job->pgid != -1)
			return (ft_wake_up(&job, bg));
		else
			return (ft_display_error(bg));
	}
	else if (ft_find_job(av->next->av + 1, bg) == 1)
		return (ft_display_error2(bg, av));
	return (0);
}
