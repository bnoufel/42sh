/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_query.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:38:28 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:38:29 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char				*get_open_dir(char *str)
{
	char			*open;
	int				len;
	int				i;

	i = -1;
	if ((!ft_strchr(str, '/'))
	|| (str && str[0] == '*' && str[1] && str[1] == '/'))
	{
		if (!(open = getcwd(NULL, PATH_MAX)))
			(!(open = ft_strdup("/"))) ? malloc_failed("get_open_dir") : 0;
	}
	else
	{
		len = (int)ft_strlen(str);
		if (!(open = (char *)malloc(sizeof(char) * (len + 1))))
			malloc_failed("get_open_dir");
		while (str[len] != '/')
			len--;
		while (str[++i] && i < len)
			open[i] = str[i];
		open[i] = '\0';
	}
	if (!(open = ft_strjoinfree(open, "/", 1)))
		malloc_failed("get_open_dir");
	return (open);
}

static size_t		count_file(char *open)
{
	size_t			len;
	DIR				*odir;

	len = 0;
	if (!(odir = opendir(open)))
		return (1);
	while (readdir(odir))
		len++;
	closedir(odir);
	return (len);
}

static void			parkour(t_star *tree, char ***star, t_split *spl, int *i)
{
	int		j;
	char	*t;

	if (!tree)
		return ;
	parkour(tree->left, star, spl, i);
	if (tree->entry[0] != '.' && match(tree->entry, spl->middle)
	&& (spl->after[0] != '/' || tree->mode == DT_DIR || tree->mode == DT_LNK))
	{
		if (!((*star)[*i] = ft_strjoinfree(dupspec(spl->before),
		dupspec(tree->entry), 3)))
			malloc_failed("star_bind");
		if (!((*star)[*i] = ft_strjoinfree((*star)[*i], spl->after, 1)))
			malloc_failed("star_bind");
		j = 1;
		while ((*star)[*i] && (t = (*star)[*i]) && j)
			(*star)[*i] = glob_core_while((*star)[*i], &j, (*g_global->var), 1);
		(*star)[*i] ? (*i)++ : ft_strdel(&t);
	}
	parkour(tree->right, star, spl, i);
	ft_strdel(&(tree->entry));
	free(tree);
	tree = NULL;
}

static void			star_bind(char ***star, t_split *spl, DIR *odir)
{
	int				i;
	t_dirent		*rdir;
	t_star			*sort;
	char			*temp;

	i = 0;
	sort = NULL;
	while ((rdir = readdir(odir)))
		insert_data(&sort, rdir);
	temp = spl->middle;
	spl->middle = bckslshav(spl->middle, chardelim(spl->middle));
	ft_strdel(&temp);
	parkour(sort, star, spl, &i);
	(*star)[i] = 0;
}

char				*star_parser(char **str, int *j)
{
	DIR				*odir;
	t_split			split;
	char			**star;
	char			*open;

	odir = NULL;
	split_folder_star(&split, *str);
	if (!initstarquery(&odir, &open, &split))
		return (NULL);
	if (!(star = (char **)malloc(sizeof(char *) * (count_file(open) + 1))))
		malloc_failed("star_parser");
	star_bind(&star, &split, odir);
	if (star[0])
	{
		*j = 1;
		ft_strdel(str);
		*str = transform_tab_to_char(star);
	}
	ft_free_tab(star);
	closedir(odir);
	ft_strdel(&open);
	free_struct_folder(&split);
	return (*str);
}
