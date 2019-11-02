/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:37 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:38 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

bool				is_bin(char *str, char *path)
{
	char			*name;
	t_stat			st;

	if (!(name = ft_strjoin(path, "/")))
		malloc_failed("if_bin");
	if (!(name = ft_strjoinfree(name, str, 1)))
		malloc_failed("if_bin");
	if (stat(name, &st) == -1)
	{
		free(name);
		return (false);
	}
	if ((st.st_mode & S_IXUSR))
	{
		free(name);
		return (true);
	}
	free(name);
	return (false);
}

void				get_binaries(t_bin **bin, t_env *env)
{
	char			**split;
	int				i;
	DIR				*odir;
	t_dirent		*rdir;

	i = -1;
	split = NULL;
	if (retenv(env, "PATH") && !(split = ft_strsplit(retenv(env, "PATH"), ':')))
		malloc_failed("get_bin");
	while (split && split[++i])
	{
		if (!(odir = opendir(split[i])))
			continue ;
		while ((rdir = readdir(odir)))
		{
			if (rdir->d_name[0] == '.')
				continue ;
			if (is_bin(rdir->d_name, split[i]))
				*bin = ft_create_elem(*bin, rdir->d_name, split[i]);
		}
		closedir(odir);
	}
	ft_free_tab(split);
}

size_t				ft_size_bin(t_bin *bin)
{
	size_t			len;
	t_bin			*tmp;

	tmp = bin;
	len = bin ? bin->hash : 0;
	while (tmp)
	{
		if (tmp->hash > len)
			len = tmp->hash;
		tmp = tmp->next;
	}
	return (len);
}
