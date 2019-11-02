/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plist_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:49 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:49 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			freeavs(t_par **list)
{
	t_av	*tofree;
	t_par	*temp;

	while ((*list)->lav)
	{
		ft_strdel(&(*list)->lav->av);
		tofree = (*list)->lav;
		(*list)->lav = (*list)->lav->next;
		free(tofree);
		tofree = NULL;
	}
	while ((*list)->tofree)
	{
		temp = (*list)->tofree;
		(*list)->tofree = (*list)->tofree->next;
		free(temp);
		temp = NULL;
	}
}

void			ft_plist_clear(t_par **begin_list)
{
	t_par	*list;
	t_par	*prev;

	prev = NULL;
	list = *begin_list;
	while (list)
	{
		prev = list->next;
		list->prev = NULL;
		freeavs(&list);
		ft_bzero(list, sizeof(list));
		free(list);
		list = prev;
		prev = NULL;
	}
	list = NULL;
	*begin_list = NULL;
}
