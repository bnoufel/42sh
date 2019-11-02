/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:09 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:18 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char			*whichone(char **tmp, char **str, int *i)
{
	if (!(*tmp = ft_find_in_history(0, 1)))
		return (ft_strdup("!!"));
	ft_delete_word(str, *i, 2);
	ft_realloc_with_pos(str, *tmp, *i);
	if (!*str)
		return (ft_strdup(" too long"));
	(*i) += (int)ft_strlen(*tmp);
	ft_strdel(tmp);
	return (NULL);
}

char			*whichtwo(char **tmp, char **str, int *i)
{
	int			nu;
	int			n;

	n = 0;
	nu = 0;
	while ((*str)[(*i) + 1 + nu] >= '0' && (*str)[(*i) + 1 + nu] <= '9')
		nu++;
	if (nu > 9)
		return (ft_strdup("error len"));
	n = ft_atoi((*str) + (*i) + 1);
	if (!(*tmp = ft_find_in_history(n, 0)))
		return (ft_lltoa(n));
	ft_delete_word(str, *i, ft_find_r(n) + 1);
	ft_realloc_with_pos(str, *tmp, *i);
	if (!*str)
		return (ft_strdup(" too long"));
	(*i) += (int)ft_strlen(*tmp);
	ft_strdel(tmp);
	return (NULL);
}

char			*whichthree(char **tmp, char **str, int *i, char **tmp2)
{
	*tmp = ft_cut_str((*str) + (*i) + 1);
	if (!(*tmp2 = ft_find_in_history2(*tmp)))
		return (*tmp);
	ft_delete_word(str, *i, (int)ft_strlen(*tmp2));
	ft_realloc_with_pos(str, *tmp2, *i);
	if (!*str)
		return (ft_strdup(" too long"));
	ft_strdel(tmp2);
	(*i) += (int)ft_strlen(*tmp);
	ft_strdel(tmp);
	return (NULL);
}

t_history		*ft_init_history(void)
{
	t_history	*new;

	new = NULL;
	if (!(new = (t_history*)malloc(sizeof(t_history))))
		malloc_failed("ft_init_history");
	ft_bzero(new, sizeof(t_history));
	new->list = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->head = -1;
	new->file = 1;
	return (new);
}
