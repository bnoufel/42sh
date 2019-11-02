/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:10 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:18 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

/*
** Fonction qui supprime le mot a l'indice i
*/

void		ft_delete_word(char **str, int i, int number)
{
	int j;

	j = 0;
	while ((*str)[i] && (*str)[i] != ' ' && j < number)
	{
		ft_delete_realloc(str, i + 1);
		j++;
	}
}

char		*ft_find_in_history2(char *to_find)
{
	t_history	*histo;
	int			count;
	char		*tmp;

	count = 0;
	histo = (*g_global->cursor)->history;
	while (histo->prev)
	{
		tmp = list_to_char(histo->list);
		if ((ft_strstr(tmp, to_find)))
			return (tmp);
		free(tmp);
		histo = histo->prev;
		count++;
	}
	return (NULL);
}
