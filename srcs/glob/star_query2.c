/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_query2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:38:34 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:38:35 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			match(char *s1, char *s2)
{
	if (*s1 == '\0' && *s2 == '\0')
		return (1);
	else if (*s1 == '\0' && *s2 != '*')
		return (0);
	else if (*s1 == *s2)
		return (match(s1 + 1, s2 + 1));
	else if (*s2 == '*' && *s1)
		return (match(s1 + 1, s2) || match(s1 + 1, s2 + 1)
		|| match(s1, s2 + 1));
	else if (*s2 == '*' && !(*s1))
		return (match(s1, s2 + 1));
	else if (*s2 == '?' && *s1)
		return (match(s1 + 1, s2 + 1));
	else
		return (0);
}

t_star		*create_node(t_dirent *rdir)
{
	t_star	*new;

	if (!(new = (t_star *)malloc(sizeof(t_star))))
		malloc_failed("create_node");
	if (!(new->entry = ft_strdup(rdir->d_name)))
		malloc_failed("create_node");
	new->mode = rdir->d_type;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void		insert_data(t_star **root, t_dirent *rdir)
{
	t_star	*tree;

	tree = *root;
	if (!tree)
		*root = create_node(rdir);
	else
	{
		if (ft_strcmp(tree->entry, rdir->d_name) > 0)
			insert_data(&tree->left, rdir);
		else
			insert_data(&tree->right, rdir);
	}
}

int			initstarquery(DIR **odir, char **open, t_split *split)
{
	*open = split->before;
	split->before = bckslshav(split->before, chardelim(split->before));
	ft_strdel(open);
	*open = get_open_dir(split->before);
	if (!(*odir = opendir(*open)))
	{
		free_struct_folder(split);
		ft_strdel(open);
		return (0);
	}
	return (1);
}
