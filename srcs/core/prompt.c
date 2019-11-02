/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:59:34 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:13 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char		*prompt_user(void)
{
	char		*home;
	t_passwd	*uid;

	home = NULL;
	uid = getpwuid(getuid());
	if (!uid)
	{
		if (!(home = ft_strdup("42sh user")))
			malloc_failed("ft_info_line");
	}
	else
	{
		if (!(home = ft_strdup(uid->pw_name)))
			malloc_failed("ft_info_line");
	}
	return (home);
}

char			*clean_path(char *path, t_var **var)
{
	char		*env;
	char		*home;
	int			i;
	int			len;

	i = 1;
	env = ft_getenv("HOME", var);
	len = (int)ft_strlen(env) - 1;
	if (ac_match(ft_getenv("PWD", var), env))
	{
		if (!(home = ft_strnew(len + ft_strlen(path) + 1)))
			malloc_failed("clean path");
		home[0] = '~';
		if (path[len + 1] != '/')
			home[i++] = '/';
		while (path[++len])
		{
			home[i] = path[len];
			i++;
		}
		home[i] = '\0';
		return (home);
	}
	(!(home = ft_strdup(path))) ? malloc_failed("clean path") : 0;
	return (home);
}

void			ft_plu(t_cursor *c, t_var **var)
{
	char		*home;
	char		*path;
	char		hostname[256];
	char		*prompt;

	if ((!(path = checkinfo(var, c, hostname))) || (c->window.ws_col == 0))
		return ;
	path = clean_path(path, var);
	home = prompt_user();
	if (!(prompt = ft_strjoinfree("\033[32;1m", home, 2)))
		malloc_failed("ft_info_line");
	if (!(prompt = ft_strjoinfree(prompt, "\x1b[0m at \x1b[1;4;33m", 1)))
		malloc_failed("ft_info_line");
	if (!(prompt = ft_strjoinfree(prompt, ft_putstr_special(hostname, '.'), 3)))
		malloc_failed("ft_info_line");
	if (!(prompt = ft_strjoinfree(prompt, "\x1b[0m in \x1b[1;31m", 1)))
		malloc_failed("ft_info_line");
	if (!(prompt = ft_strjoinfree(prompt, path, 3)))
		malloc_failed("ft_info_line");
	prompt_git(&prompt);
	if (!(prompt = ft_strjoinfree(prompt, "\033[0m", 1)))
		malloc_failed("ft_info_line");
	c->add_line = 1 + ((int)(ft_strlen(prompt) - 62) / c->window.ws_col);
	free(prompt);
}

void			ft_info_line(t_cursor *c, t_var **var)
{
	char		*home;
	char		*path;
	char		hostname[256];
	char		*p;

	if ((!(path = checkinfo(var, c, hostname))) || (c->window.ws_col == 0))
		return ;
	path = clean_path(path, var);
	home = prompt_user();
	if (!(p = ft_strjoinfree("\033[32;1m", home, 2)))
		malloc_failed("ft_info_line");
	if (!(p = ft_strjoinfree(p, "\x1b[0m at \x1b[1;4;33m", 1)))
		malloc_failed("ft_info_line");
	if (!(p = ft_strjoinfree(p, ft_putstr_special(hostname, '.'), 3)))
		malloc_failed("ft_info_line");
	if (!(p = ft_strjoinfree(p, "\x1b[0m in \x1b[1;31m", 1)))
		malloc_failed("ft_info_line");
	(!(p = ft_strjoinfree(p, path, 3))) ? malloc_failed("line") : 0;
	prompt_git(&p);
	if (!(p = ft_strjoinfree(p, "\033[0m", 1)))
		malloc_failed("ft_info_line");
	c->add_line = 1 + ((int)(ft_strlen(p) - 58) / c->window.ws_col);
	ft_putendl_fd(p, 0);
	free(p);
}
