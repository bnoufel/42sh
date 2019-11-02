/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:43 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:44 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

unsigned long		hash(char *str)
{
	unsigned long	hash;
	int				c;

	hash = 0;
	if (!str)
		return (0);
	while ((c = *str++))
		hash += c;
	return (hash);
}

t_bin				*ft_create_elem(t_bin *lst, char *name, char *path)
{
	t_bin			*tmp;

	if (!(tmp = (t_bin *)malloc(sizeof(t_bin))))
		malloc_failed("ft_create_elem");
	if (!(tmp->name = ft_strdup(name)))
		malloc_failed("ft_create_elem");
	if (!(tmp->path = ft_strjoin(path, "/")))
		malloc_failed("ft_create_elem");
	if (!(tmp->path = ft_strjoinfree(tmp->path, name, 1)))
		malloc_failed("ft_create_elem");
	tmp->hash = hash(name);
	tmp->next = lst;
	return (tmp);
}

void				*ft_create_elem_hash(t_hash *lst, char *name, char *path)
{
	t_hash			*tmp;

	if (!(tmp = (t_hash *)malloc(sizeof(t_hash))))
		malloc_failed("ft_create_elem_hash");
	if (!(tmp->name = ft_strdup(name)))
		malloc_failed("ft_create_elem");
	if (!(tmp->path = ft_strdup(path)))
		malloc_failed("ft_create_elem");
	tmp->next = lst;
	return (tmp);
}
