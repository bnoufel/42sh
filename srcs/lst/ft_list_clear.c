/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:45 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:46 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_list_clear(t_env **begin_list)
{
	t_env *list;
	t_env *prev;

	prev = NULL;
	list = *begin_list;
	while (list)
	{
		prev = list->next;
		ft_bzero(list->elem, sizeof(list->elem));
		free(list);
		list = prev;
		prev = NULL;
	}
	list = NULL;
	*begin_list = NULL;
}
