/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:04:00 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:04:14 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void				ac_free_auto(t_auto *head)
{
	t_auto			*tmp;

	while (head->prev->head != 1)
		head = head->next;
	while (head->head != 1)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp->path);
		free(tmp->after);
		free(tmp->color);
		free(tmp);
	}
	free(head);
}

void				ac_free_struct(t_split *folder)
{
	free(folder->before);
	free(folder->middle);
	free(folder->after);
	free(folder);
}
