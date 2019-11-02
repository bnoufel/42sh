/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:05 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:17 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

/*
** Fonction qui va realloc une chaine en mettant une autre chaine a la position
*/

void			ft_realloc_with_pos(char **str, char *place, int pos)
{
	char		*new;
	int			size;
	int			i;
	int			j;
	int			k;

	j = 0;
	i = 0;
	k = 0;
	size = (int)ft_strlen(*str) + (int)ft_strlen(place);
	if (!(new = (char*)malloc(sizeof(char) * (size + 1))))
		malloc_failed("realloc_with_pos");
	while ((*str)[i] && i < size && i < 10000)
	{
		if (i == pos && place[j])
		{
			while (place[j])
				new[k++] = place[j++];
		}
		else
			new[k++] = (*str)[i++];
	}
	new[k] = '\0';
	ft_strdel(str);
	i == 10000 ? ft_strdel(&new) : (*str = new);
}

/*
** 0 == !!
** 1 == !450
** 2 == !jkdsfhfdksg
** 3 == rien
*/

char			*ft_cut_str(char *str)
{
	char		*new;
	char		*c;
	int			i;

	i = 0;
	if (!(new = (char *)ft_strnew(10)))
		malloc_failed("cut_str");
	while (str[i])
	{
		if (str[i] == ' ')
			break ;
		if (str[i] == '!')
			break ;
		if (!(c = ft_chardup(str[i])))
			malloc_failed("cut_str");
		if (!(new = ft_strjoinfree(new, c, 3)))
			malloc_failed("cut_str");
		i++;
	}
	return (new);
}

char			*ft_find_which(char **str, int *i)
{
	char		*tmp;
	char		*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if ((*str)[(*i) + 1] == '!')
		return (whichone(&tmp, str, i));
	else if ((*str)[(*i) + 1] >= '1' && (*str)[(*i) + 1] <= '9')
		return (whichtwo(&tmp, str, i));
	else if ((*str)[(*i) + 1] >= 34 && (*str)[(*i) + 1] <= 126)
		return (whichthree(&tmp, str, i, &tmp2));
	else
		(*i)++;
	return (NULL);
}

/*
** !45   faire atoi et recuperer le nombre, realloc avec ce qui suit
** !!    remplacer !! par derniere commande
** !ls   prendre la chaine jusqu'a un espace ou
** la fin de la chaine ex : "!ls98 lol " on recherche 'ls98'
*/

void			ft_built_in_exc(char **str)
{
	int			i;
	char		*tmp;

	i = 0;
	if ((!(*g_global->cursor)->history->prev->prev) || (*str[0] != '!'))
		return ;
	while ((*str)[i])
	{
		if ((*str)[i] == '!')
		{
			if ((tmp = ft_find_which(str, &i)))
			{
				ft_putstr_fd("fun_sh: no such event: ", 0);
				free(*str);
				ft_putendl_fd(tmp, 0);
				free(tmp);
				*str = NULL;
				return ;
			}
			continue;
		}
		i++;
	}
	ft_str_to_list(*str, g_global->list);
}
