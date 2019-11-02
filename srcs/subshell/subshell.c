/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:01:14 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:15 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char		*ft_free_join(char *str1, char *str2, int i)
{
	char	*to_return;

	to_return = NULL;
	if (i && !str1)
		return (ft_strdup(str2));
	else if (i)
	{
		if (!(to_return = ft_strjoin(str1, str2)))
			malloc_failed("ft_free_join");
		ft_strdel(&str1);
	}
	return (to_return);
}

char		*read_fd(int fd, int quotes)
{
	char	c[2];
	char	buff[4096];
	int		i;
	int		o;
	char	*str;

	i = 0;
	str = NULL;
	while ((o = read(fd, c, 1)) > 0)
	{
		c[1] = '\0';
		buff[i++] = (c[0] == '\n' && quotes == 0) ? ' ' : c[0];
		if (i == 4095)
		{
			buff[i] = '\0';
			str = ft_free_join(str, buff, i);
			i = 0;
		}
	}
	buff[i] = '\0';
	i && buff[i - 1] == ' ' ? (buff[i - 1] = '\0') : 0;
	str = ft_free_join(str, buff, i);
	return (str);
}

int			newpid(void)
{
	t_pid	*spid;
	t_pid	*myg;

	myg = g_global->pid;
	if (!(spid = (t_pid *)malloc(sizeof(t_pid))))
		malloc_failed("newpid");
	spid->pid = getpid();
	spid->next = NULL;
	while (myg && myg->next)
		myg = myg->next;
	myg->next = spid;
	return (1);
}

static char	*subshell(char *cmd, int q, t_var **var, char *s)
{
	pid_t	pid;
	int		fds[2];

	pid = 0;
	if (pipe(fds) < 0 || (pid = fork()) == -1)
	{
		ft_putendl_fd("mysh: resource temporarily unavailable", 2);
		g_global->sig = 1;
		ft_strdel(&cmd);
		return (NULL);
	}
	else if (!pid && newpid() && dup2(fds[1], STDOUT_FILENO))
	{
		fds[1] > g_global->fdmax ? g_global->fdmax = fds[1] : 0;
		ft_open_sig();
		setpgid(getpid(), getpid());
		ft_pgid(getpgrp(), getpid());
		g_global->is_scrpt ? tcsetpgrp(g_global->f_fd, getpid())
		: tcsetpgrp(0, getpid());
		cmd && (s = ft_strdup(cmd)) ? 0 : malloc_failed("subshell");
		g_global->ret = eval(&s, var);
		close_fdmax();
		ft_bye_bye(var, 0, NULL, g_global->ret);
	}
	return (helpinsub(pid, q, fds));
}

char		*parse_subshell(char *cmd, t_var **var, int q)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 40 || cmd[i] == 96)
		{
			(g_global->sub)++;
			tmp = subshell(cmd + i + 1, q, var, NULL);
			ft_strdel(&cmd);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}
