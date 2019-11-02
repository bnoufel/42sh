/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_auto.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:06:23 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:06:25 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			ft_add_auto(t_auto **list, char *str, char *to_open)
{
	t_auto		*new;

	if (!(new = (t_auto *)malloc(sizeof(t_auto))))
		malloc_failed("add_elem");
	(*list)->next = new;
	new->prev = *list;
	new->next = NULL;
	if (!(new->str = ft_strdup(str)))
		malloc_failed("ft_strdup");
	if (!(new->path = ft_strdup(to_open)))
		malloc_failed("ft_strdup");
	new->size = (int)ft_strlen(str);
	new->head = 0;
	new->selected = 0;
	new->color = NULL;
	new->after = NULL;
}

void			ft_head_auto(t_auto **list)
{
	if (!(*list = (t_auto*)malloc(sizeof(t_auto))))
		malloc_failed("init_list");
	(*list)->str = NULL;
	(*list)->path = NULL;
	(*list)->head = 1;
	(*list)->selected = -1;
	(*list)->next = NULL;
	(*list)->prev = NULL;
	(*list)->color = NULL;
}

void			ft_list_auto(t_auto **list, char *str, char *to_open)
{
	ft_add_auto(list, str, to_open);
	*list = (*list)->next;
}

int				ft_autolen(t_auto *list)
{
	int			nb;

	nb = 0;
	while (list->head != 1)
	{
		nb++;
		list = list->next;
	}
	return (nb);
}
