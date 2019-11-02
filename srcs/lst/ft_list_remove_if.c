/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:47 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:48 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static	void	checkpath(char *data_ref, int (*equ)())
{
	if (equ(data_ref, "PATH"))
	{
		clean_tab();
		clean_bin();
	}
}

static t_env	*check_first(t_env **begin_list, char *data_ref, int (*equ)())
{
	t_env *list;
	t_env *temp;

	list = *begin_list;
	if (list && list->next == NULL && equ(list->elem, data_ref))
	{
		checkpath(list->elem, equ);
		ft_bzero(list->elem, sizeof(list->elem));
		free(*begin_list);
		*begin_list = NULL;
		list = NULL;
		return (0);
	}
	while (list && equ(list->elem, data_ref) != 0 && list)
	{
		checkpath(list->elem, equ);
		temp = list;
		list = list->next;
		ft_bzero(temp->elem, sizeof(temp->elem));
		free(temp);
	}
	*begin_list = list;
	return (list);
}

int				ft_list_remove_if(t_env **begin_list, char *data_ref,
		int (*equ)())
{
	t_env	*list;
	t_env	*prev;
	t_env	*temp;

	prev = NULL;
	list = check_first(begin_list, data_ref, (int(*)())equ);
	while (list)
	{
		if (equ(list->elem, data_ref) == 1)
		{
			checkpath(list->elem, equ);
			temp = list;
			list = list->next;
			prev ? prev->next = list : 0;
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
