/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:04:41 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:04:45 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static bool		ac_read_add_lst(char *name,
									char *middle, t_stat *st, char **to_open)
{
	char		*path;

	if (!(path = ft_strjoinfree(ac_open_folder(middle, '/'), "/", 1)))
		malloc_failed("ac_read_path_bin3");
	(!(*to_open = ft_strdup(path))) ? malloc_failed("ft_strdup") : 0;
	if (!(path = ft_strjoinfree(path, ac_add_backslash(name), 3)))
		malloc_failed("ac_read_path_bin3");
	if (stat(ac_remove_backslash(path), st) == -1)
	{
		free(path);
		return (false);
	}
	free(path);
	return (true);
}

static void		ac_read_path_bin3(DIR *odir, t_split *fold,
													t_auto **lst, int bin)
{
	t_dirent	*rdir;
	t_stat		st;
	char		*to_open;
	char		*tmp;

	while ((rdir = readdir(odir)))
	{
		tmp = ac_add_backslash(rdir->d_name);
		if (!(ac_read_add_lst(rdir->d_name, fold->middle, &st, &to_open)))
		{
			free(to_open);
			free(tmp);
			continue ;
		}
		if (rdir->d_name[0] != '.' && bin == 2 && S_ISDIR(st.st_mode)
		&& (ac_match(tmp, ft_strrchr(fold->middle, '/') + 1)
			|| match(tmp, ft_strrchr(fold->middle, '/') + 1)))
			ft_list_auto(lst, tmp, to_open);
		else if (rdir->d_name[0] != '.' && bin != 2
		&& (ac_match(tmp, ft_strrchr(fold->middle, '/') + 1)
			|| match(tmp, ft_strrchr(fold->middle, '/') + 1)))
			ft_list_auto(lst, tmp, to_open);
		free(to_open);
		free(tmp);
	}
}

static bool		ac_read_path_bin2(t_split *folder,
											t_auto **lst, int bin, char *old)
{
	char		*to_open;
	DIR			*odir;

	if (!(to_open = ac_open_folder(folder->middle, '/')))
		return (false);
	if (!(odir = opendir(ac_remove_backslash(to_open))))
	{
		free(to_open);
		return (false);
	}
	ac_read_path_bin3(odir, folder, lst, bin);
	closedir(odir);
	free(to_open);
	if (bin == 1 && (*lst)->str == NULL && !ft_strchr(old, '/'))
		ac_read_builtin(lst, folder);
	return (true);
}

t_auto			*ac_read_path_bin(t_split *folder, int bin, char *old)
{
	t_auto		*lst;
	t_auto		*head;

	lst = NULL;
	ft_head_auto(&lst);
	head = lst;
	if (!(ac_read_path_bin2(folder, &lst, bin, old)))
	{
		free(head);
		free(old);
		return (NULL);
	}
	lst->next = head;
	head->prev = lst;
	free(folder->middle);
	if (!(folder->middle = ft_strdup(old)))
		malloc_failed("ac_read_path_bin");
	free(old);
	return (head);
}
