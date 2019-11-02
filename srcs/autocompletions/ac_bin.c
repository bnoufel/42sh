/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:03:33 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:09:26 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char		**ac_builtin(void)
{
	char		**builtin;

	if (!(builtin = (char **)malloc(sizeof(char *) * 17)))
		malloc_failed("ac_builtin");
	(!(builtin[0] = ft_strdup("echo"))) ? malloc_failed("ac_builtin") : 0;
	(!(builtin[1] = ft_strdup("cd"))) ? malloc_failed("ac_builtin") : 0;
	(!(builtin[2] = ft_strdup("setenv"))) ? malloc_failed("ac_builtin") : 0;
	(!(builtin[3] = ft_strdup("unsetenv"))) ? malloc_failed("ac_builtin") : 0;
	(!(builtin[4] = ft_strdup("env"))) ? malloc_failed("ac_builtin") : 0;
	(!(builtin[5] = ft_strdup("history"))) ? malloc_failed("ac_builtin") : 0;
	(!(builtin[6] = ft_strdup("export"))) ? malloc_failed("ac_builtin") : 0;
	(!(builtin[7] = ft_strdup("set"))) ? malloc_failed("ac_builtin") : 0;
	(!(builtin[8] = ft_strdup("unset"))) ? malloc_failed("ac_builtin") : 0;
	(!(builtin[9] = ft_strdup("exit"))) ? malloc_failed("ac_builtin") : 0;
	(!(builtin[10] = ft_strdup("read"))) ? malloc_failed("ac_builtin") : 0;
	(!(builtin[11] = ft_strdup("infosh"))) ? malloc_failed("ac_builtin") : 0;
	(!(builtin[12] = ft_strdup("jobs"))) ? malloc_failed("ac_builtin") : 0;
	(!(builtin[13] = ft_strdup("bg"))) ? malloc_failed("ac_builtin") : 0;
	(!(builtin[14] = ft_strdup("fg"))) ? malloc_failed("ac_builtin") : 0;
	(!(builtin[15] = ft_strdup("reload"))) ? malloc_failed("ac_builtin") : 0;
	builtin[16] = 0;
	return (builtin);
}

static bool		ac_readdir_bin2(t_auto **lt, t_split *folder, char *env, int i)
{
	DIR			*odir;
	t_dirent	*rdir;
	char		**split;

	if (!env)
		return (false);
	(!(split = ft_strsplit(env, ':'))) ? malloc_failed("ac_readdir_bin") : 0;
	while (split[++i])
	{
		if (!(odir = opendir(split[i])))
			continue ;
		while ((rdir = readdir(odir)))
		{
			if (rdir->d_name[0] != '.'
				&& (match(rdir->d_name, folder->middle)
				|| ac_match(rdir->d_name, folder->middle)))
				ft_list_auto(lt, rdir->d_name, split[i]);
		}
		closedir(odir);
	}
	ft_free_tab(split);
	return (true);
}

static void		bin_in_cwd(t_split *folder)
{
	char		*tmp;
	char		*cwd;

	if (!(cwd = getcwd(NULL, PATH_MAX)))
	{
		if (!(cwd = ft_strdup("/")))
			malloc_failed("ac_get_occu");
	}
	if (!(tmp = ft_strdup(folder->middle)))
		malloc_failed("ac_get_occu");
	free(folder->middle);
	if (!(folder->middle = ft_strjoinfree(cwd, "/", 1)))
		malloc_failed("ac_get_occu");
	if (!(folder->middle = ft_strjoinfree(folder->middle, tmp, 3)))
		malloc_failed("ac_get_occu");
}

t_auto			*ac_readdir_bin(char *env, t_split *folder, int index, int bin)
{
	t_auto		*lst;
	t_auto		*head;
	char		*old;

	(!(old = ft_strdup(folder->middle))) ? malloc_failed("ac_readdir_bin") : 0;
	lst = NULL;
	ft_head_auto(&lst);
	head = lst;
	if (!env)
	{
		free(head);
		return (ac_read_path_bin(folder, bin, old));
	}
	if (!(ac_readdir_bin2(&lst, folder, env, index)))
		return (NULL);
	if (lst->str == NULL)
	{
		(folder->middle[0] != '\0') ? bin_in_cwd(folder) : 0;
		free(head);
		return (ac_read_path_bin(folder, bin, old));
	}
	lst->next = head;
	head->prev = lst;
	free(old);
	return (head);
}

void			ac_read_builtin(t_auto **lst, t_split *folder)
{
	char		**builtin;
	int			i;

	i = 0;
	builtin = ac_builtin();
	while (builtin[i])
	{
		if ((ac_match(builtin[i], ft_strrchr(folder->middle, '/') + 1)
			|| match(builtin[i], ft_strrchr(folder->middle, '/') + 1)))
			ft_list_auto(lst, builtin[i], "");
		i++;
	}
	ft_free_tab(builtin);
}
