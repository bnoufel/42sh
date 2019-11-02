/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_sh2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:48 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:51 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		ft_display_arrow(int n)
{
	char toto[4];

	toto[0] = 0xE2;
	toto[1] = 0x87;
	if (n == 0)
		toto[2] = 0xA6;
	else if (n == 1)
		toto[2] = 0xA7;
	else if (n == 2)
		toto[2] = 0xA8;
	else if (n == 3)
		toto[2] = 0xA9;
	toto[3] = '\0';
	ft_putstr("\033[32m");
	ft_putstr(toto);
	ft_putstr("\033[0m");
}

/*
** 0 -> suppr
** 1 -> delete
** 2 -> option
*/

void		ft_display_delete(int n)
{
	char toto[4];

	toto[0] = 0xE2;
	toto[1] = 0x8C;
	if (n == 1)
		toto[2] = 0xAB;
	else if (n == 0)
		toto[2] = 0xA6;
	else if (n == 2)
		toto[2] = 0xA5;
	toto[3] = '\0';
	ft_putstr("\033[32m");
	ft_putstr(toto);
	ft_putstr("\033[0m");
}

void		ft_display_enter(void)
{
	char toto[4];

	toto[0] = 0xE2;
	toto[1] = 0x8F;
	toto[2] = 0x8E;
	toto[3] = '\0';
	ft_putstr("\033[32m");
	ft_putstr(toto);
	ft_putstr("\033[0m");
}

void		ft_display_tab(void)
{
	char toto[4];

	toto[0] = 0xE2;
	toto[1] = 0x86;
	toto[2] = 0xB9;
	toto[3] = '\0';
	ft_putstr("\033[32m");
	ft_putstr(toto);
	ft_putstr("\033[0m");
}
