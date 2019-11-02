/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:05:44 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:05:47 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static	void	ft_assign(char c, t_list **copy)
{
	(*copy)->c = c;
	(*copy)->next = NULL;
	(*copy)->state = 0;
	(*copy)->selected = 0;
	(*copy)->erase = 0;
	(*copy)->qdbs = 0;
}

void			ft_str_to_list(char *str, t_list **list)
{
	int			i;
	t_list		*tmp;

	i = 0;
	while ((*list)->prev)
		*list = (*list)->prev;
	while ((*list)->next->next)
		ft_free_right_node(list);
	tmp = (*list)->next;
	while (str[i])
	{
		if (!((*list)->next = (t_list*)malloc(sizeof(t_list))))
			malloc_failed("ft_empty_line");
		ft_assign(str[i], &(*list)->next);
		(*list)->next->prev = *list;
		*list = (*list)->next;
		i++;
	}
	(*list)->next = tmp;
	tmp->prev = *list;
	while ((*list)->next->next)
		*list = (*list)->next;
	(*list)->next->state = 1;
}

static int		ft_first_bin(char *str, int number)
{
	int			i;

	i = 0;
	while (i < number)
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int		ft_is_cd_first(char *str)
{
	int			i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if ((ft_strequ(str, "cd") || ft_strequ(str, "/bin/cd")))
		return (1);
	return (0);
}

/*
** @brief
** 0 = cas d'erreur
** 1 = 1er elem = bin
** 2 = pas 1er elem + bin = cd
** @param list
** @param cursor
*/

int				ft_find_elem(char *str, int number)
{
	int			i;
	int			cd;

	i = 0;
	cd = 0;
	if (ft_first_bin(str, number))
		return (1);
	else if (str[number] == ' ' && !(ft_is_cd_first(str)))
		return (0);
	else
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && str[i + 1] && (ft_strequ(str, "cd")
		|| ft_strequ(str, "/bin/cd")))
			cd = 1;
		while (str[i] && str[i] != ' ')
			i++;
		if (i == number + 1)
			return (1);
		else
			return ((cd == 1) ? (2) : (0));
	}
}
