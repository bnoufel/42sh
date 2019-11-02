/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listlen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:50 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:03:10 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		listlen(t_env *list)
{
	int i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}
