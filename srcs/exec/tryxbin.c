/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tryxbin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:07:55 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:07:56 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int		checkbang(t_par **cur)
{
	int		fd;
	char	*gs;
	int		c;

	if (!ckfav(cur, 0))
		return (0);
	if (access((*cur)->av[0], X_OK))
		return (0);
	if ((fd = open((*cur)->av[0], O_RDONLY)) == -1)
		return (0);
	while (gnl(fd, &gs, 1) > 0)
	{
		if (!isbin(gs) && (c = hashkey(cur, &gs)) == 1)
			;
		else if (c == 2 && !close(fd))
			return (2);
		else if (!close(fd))
			return (0);
	}
	close(fd);
	return (0);
}

char			*retenv(t_env *env, char *occur)
{
	while (env)
	{
		if (env_strequ(env->elem, occur))
			return (env->elem + ft_strlen(occur) + 1);
		env = env->next;
	}
	return (0);
}

void			endofexec(t_par **cur, int pid, int fd[2])
{
	int r;

	r = 0;
	dealwfds2(cur);
	if (ft_strcmp((*cur)->action, "|") && !ft_isdigit((*cur)->action[0]))
		bofg(pid, &r, *cur, fd);
	if ((*cur)->sub && (*cur)->lav && (*cur)->lav->av[0] == 40)
		g_global->sub--;
}

void			buildtabav(t_par **par, int f)
{
	t_par	*cur;
	t_av	*save;
	int		i;

	i = 0;
	cur = *par;
	save = cur->lav;
	if (!(cur->av = (char **)malloc((cur->ac + 1 + f) * sizeof(char *))))
		malloc_failed("toforkornot");
	while (cur->lav)
	{
		!(cur->av[i++] = ft_strdup(cur->lav->av))
		? malloc_failed("buildtabav") : 0;
		cur->lav = cur->lav->next;
	}
	cur->lav = save;
	cur->av[i] = 0;
	*par = cur;
}

void			exec(t_var *var, char *m, t_par *cur)
{
	char	*line;

	buildtabav(&cur, 0);
	if ((!cur->av[0] || !cur->av[0][0]))
		ft_bye_bye(&var, 0, NULL, 0);
	ft_strlen((line = get_hash(cur->av[0]))) < PATH_MAX - 2 ?
	ft_strcpy(m, line) : 0;
	if (m[0] && (line = ft_strjoin("_=", m))
	&& !ft_list_nchange_if(&var, line, &env_strequ, 1))
		ft_strdel(&line);
	adaptarray(&var);
	close_fdmax();
	if (checkbang(&cur) == 2)
		ft_bye_bye(&var, 0, NULL, 1);
	if ((access(cur->av[0], X_OK) || (cur->av[0][0] != '.'
	&& cur->av[0][0] != '/') || execve(cur->av[0], cur->av, var->tenv) < 0)
	&& (!m[0] || (execve(m, cur->av, var->tenv) < 0)))
	{
		write(2, "mysh: command not found: ", 25);
		ft_putendl_fd(cur->av[0], 2);
		ft_bye_bye(&var, 0, NULL, 1);
	}
}
