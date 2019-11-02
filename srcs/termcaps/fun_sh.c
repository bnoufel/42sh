/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_sh.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:45 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:47 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

/*
** 0 <=
** 1 ^
** 2 =>
** 3 V
*/

void		ft_display_third(void)
{
	ft_putstr("                     \033[32m[HOME]\033[0m or ");
	ft_putstr("\033[32m[CTRL]\033[0m + \033[32m[A]\033[0m");
	ft_putendl(" Go to the beginning");
	ft_display_delete(2);
	ft_putstr("  + ");
	ft_display_arrow(3);
	ft_putstr("     Move lower");
	ft_putstr("                     \033[32m[END]\033[0m  ");
	ft_putendl("or \033[32m[CTRL]\033[0m + \033[32m[E]\033[0m Go to the end");
	ft_display_delete(2);
	ft_putstr("  + \033[32m[X]\033[0m   Cut the selection");
	ft_putendl("              \033[32m[CTRL]\033[0m + \033[32m[R]\
	\033[0m         Search in history");
	ft_display_delete(2);
	ft_putstr("  + \033[32m[C]\033[0m   Copy the selection	");
	ft_putendl("	  If you add a binary file,");
	ft_display_delete(2);
	ft_putstr("  + \033[32m[V]\033[0m   Past the selection	");
	ft_putendl("	  use \033[32mreload\033[0m to reset the hash table");
}

void		ft_display_second(void)
{
	ft_display_delete(2);
	ft_putstr("  + ");
	ft_display_arrow(0);
	ft_putstr("     Select from here to the left");
	ft_putstr("   \033[32m[MAJ]\033[0m  + ");
	ft_display_arrow(0);
	ft_putstr("             Move word to the left");
	ft_putendl("");
	ft_display_delete(2);
	ft_putstr("  + ");
	ft_display_arrow(2);
	ft_putstr("     Select from here to the right");
	ft_putstr("  \033[32m[MAJ]\033[0m  + ");
	ft_display_arrow(2);
	ft_putstr("             Move word to the right");
	ft_putendl("");
	ft_display_delete(2);
	ft_putstr("  + ");
	ft_display_arrow(1);
	ft_putstr("     Move upper");
}

void		ft_display_first(void)
{
	ft_display_arrow(0);
	ft_putstr("   Move to the left");
	ft_putstr("                      use \033[32minfosh\033[0m ");
	ft_putendl("to display this page");
	ft_display_arrow(2);
	ft_putstr("   Move to the right");
	ft_putstr("                     ");
	ft_display_tab();
	ft_putstr("  Trigger the autocompletion");
	ft_putendl("");
	ft_display_arrow(1);
	ft_putstr("   Up in history");
	ft_putstr("                         ");
	ft_display_enter();
	ft_putstr("  Launch a command");
	ft_putendl("");
	ft_display_arrow(3);
	ft_putstr("   Down in history");
	ft_putstr("                       ");
	ft_display_delete(0);
	ft_putstr("  or ");
	ft_display_delete(1);
	ft_putstr("  delete a character");
	ft_putendl("\n");
}

int			ft_display_esc(void)
{
	ft_display_first();
	ft_display_second();
	ft_display_third();
	return (0);
}
