/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_number.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:15 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:19 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char		*list_to_char(t_list *list)
{
	t_list	*tmp;
	char	*new;

	tmp = list;
	if (!(new = ft_strnew(1)))
		malloc_failed("ft_list_to_string");
	while (tmp)
	{
		if (!(new = ft_strjoinfree(new, ft_chardup(tmp->c), 3)))
			malloc_failed("ft_list_to_string");
		tmp = tmp->next;
	}
	return (new);
}

char		*ft_find_in_history(int n, int other)
{
	t_history	*histo;
	int			count;

	count = 0;
	histo = (*g_global->cursor)->history;
	while (histo->prev)
		histo = histo->prev;
	while (histo->next->next && (count < n || other))
	{
		histo = histo->next;
		count++;
	}
	if (count < n && other == 0)
		return (NULL);
	return (list_to_char(histo->list));
}
