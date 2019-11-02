/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_compl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:04:58 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:05:03 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void				ft_display_number(int number)
{
	int i;

	ft_putstr_fd("\nDo you wish to see all ", 0);
	ft_putnbr_fd(number, 0);
	ft_putstr_fd(" possibilities ?", 0);
	i = -1;
	while (i++ < (*g_global->cursor)->col)
		ft_putendl_fd("", 0);
}

static int				ft_find_max_len(t_auto *head)
{
	int a;

	a = 0;
	while (head->head != 1)
	{
		if (head->size > a)
			a = head->size;
		head = head->next;
	}
	return (a);
}

static int				ft_calcul(int size_max)
{
	int a;

	a = (((*g_global->cursor)->window.ws_col) / (size_max + 1) - 1);
	if (a == 0)
		return (2);
	else if (a < 0)
		return (2);
	else
		return (a);
}

static void				ft_display_bis(t_auto *head, int i, int a, int size_max)
{
	ft_putstr_fd(head->color, 0);
	ft_putstr_fd(head->str, 0);
	ft_putstr_fd(RESET, 0);
	ft_putstr_fd(head->after, 0);
	while (i++ < size_max)
		ft_putstr_fd(" ", 0);
	if ((a % ft_calcul(size_max)) == 0)
		ft_putstr_fd("\n", 0);
	else
		ft_putstr_fd(" ", 0);
}

void					ft_display_compl(t_auto *head, int number)
{
	int			size_max;
	int			i;
	int			a;

	a = 1;
	if (number > 300 && (*g_global->cursor)->completion == 1)
		return (ft_display_number(number));
	(*g_global->cursor)->completion = 0;
	ft_putendl("");
	size_max = ft_find_max_len(head);
	while (head->head != 1)
	{
		i = (int)ft_strlen(head->str);
		ft_display_bis(head, i, a, size_max);
		head = head->next;
		a++;
	}
	ft_putstr_fd("\n", 0);
	i = 0;
	while (i++ < (*g_global->cursor)->col)
		ft_putendl("");
}
