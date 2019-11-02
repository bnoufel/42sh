/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dir2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:32:25 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:32:26 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				checkifpreviouslnk(char *s)
{
	int			a;
	int			i;
	struct stat st;
	char		p[PATH_MAX];
	int			len;

	len = (int)ft_strlen(s);
	i = 1;
	a = 0;
	ft_bzero(p, sizeof(p));
	while (s[0] && s[i] && a < len)
	{
		p[a] = a ? 47 : s[0];
		a++;
		while (s && !p[a] && s[i] && s[i] != 47)
			p[a++] = s[i++];
		p[a] = '\0';
		s[i] ? i++ : 0;
		lstat(p, &st);
		if (S_ISLNK(st.st_mode))
			return (1);
	}
	return (0);
}

static	int		hyphen(t_var *var, char *temp)
{
	if (chdir(g_global->spwd->old_pwd) < 0)
	{
		write(2, "cd: no such file or directory: ", 31);
		ft_putendl_fd(g_global->spwd->old_pwd, 2);
		return (1);
	}
	ft_strcpy(temp, g_global->spwd->old_pwd);
	ft_strcpy(g_global->spwd->old_pwd, g_global->spwd->pwd);
	ft_strcpy(g_global->spwd->pwd, temp);
	ft_putendl(g_global->spwd->pwd);
	actualize_env(&var);
	return (0);
}

int				handle_dirissue(char ac, t_av *av, t_var *var)
{
	int		i;
	char	temp[PATH_MAX];

	if (!(i = checkav(&av)) || ac - i >= 2)
	{
		i && ac - i >= 2 ? ft_putendl_fd("cd: too many arguments", 2) : 0;
		return (1);
	}
	ft_strcpy(g_global->spwd->old_pwd, retenv(var->lenv, "OLDPWD"));
	if ((ac - i == 1) && !ft_strcmp(av->av, "-"))
		return (hyphen(var, temp) ? 1 : 0);
	else if (ac - i == 1)
		return (dealwopt(av->av, var));
	else if (ac - i == 0)
		return (dealwopt(retenv(var->lenv, "HOME"), var));
	ft_putendl_fd("cd: too many arguments", 2);
	return (1);
}
