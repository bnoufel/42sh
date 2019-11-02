/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removeifsame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:55 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:56 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static t_env	*checkfirst(t_env **begin_list, char *data_ref, int (*cmp)())
{
	t_env *list;
	t_env *temp;

	list = *begin_list;
	if (list && list->next == NULL && !cmp(list->elem, data_ref))
	{
		ft_bzero(list->elem, sizeof(list->elem));
		free(*begin_list);
		list = NULL;
		*begin_list = NULL;
		return (0);
	}
	while (list && !cmp(list->elem, data_ref))
	{
		temp = list;
		list = list->next;
		free(temp);
	}
	*begin_list = list;
	return (list);
}

int				removeifsame(t_env **begin_list, char *data_ref,
				int (*cmp)())
{
	t_env	*list;
	t_env	*prev;
	t_env	*temp;

	prev = NULL;
	list = checkfirst(begin_list, data_ref, (int(*)())cmp);
	while (list)
	{
		if (!cmp(list->elem, data_ref))
		{
			temp = list;
			list = list->next;
			prev->next = list;
			ft_bzero(temp->elem, sizeof(temp->elem));
			free(temp);
		}
		else
		{
			prev = list;
			list = list->next;
		}
	}
	return (0);
}
