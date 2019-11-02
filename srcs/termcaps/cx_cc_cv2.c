/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cx_cc_cv2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:41 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:42 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

t_list			*ft_copy_node(t_list *list)
{
	t_list *new;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		malloc_failed("ft_realloc_term");
	ft_bzero(new, sizeof(t_list));
	new->c = list->c;
	new->next = NULL;
	new->prev = NULL;
	new->state = 0;
	new->selected = 0;
	new->erase = 0;
	return (new);
}

t_list			*ft_copy_linked_list(t_list *list, int *nb)
{
	t_list *new;
	t_list *tmp;
	t_list *head;

	if (list == NULL)
		return (NULL);
	tmp = list;
	new = ft_copy_node(list);
	head = new;
	tmp = tmp->next;
	(*nb)++;
	while (tmp)
	{
		new->next = ft_copy_node(tmp);
		new->next->prev = new;
		new = new->next;
		tmp = tmp->next;
		(*nb)++;
	}
	return (head);
}
