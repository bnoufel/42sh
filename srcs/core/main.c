/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:59:22 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:11 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int					main(int ac, char **av)
{
	t_cursor		*cursor;
	t_var			*var;

	if (!(cursor = (t_cursor*)malloc(sizeof(t_cursor))))
		malloc_failed("main");
	ft_bzero(cursor, sizeof(t_cursor));
	if (!(g_global = (t_global *)malloc(sizeof(t_global))))
		malloc_failed("global");
	set_signal_main();
	ft_bzero((void*)g_global, sizeof(t_global));
	cursor->history = NULL;
	g_global->buckets = NULL;
	g_global->bin = NULL;
	var = init_var();
	init_cursor(cursor, 1);
	ft_jobs(-1, "head", NULL);
	init_g(&var, ac, av, &cursor);
	init_term(cursor, 1, &var, 1);
	ft_open(cursor);
	signal(SIGINT, ft_catch_sig);
	signal(SIGWINCH, ft_catch_sig);
	ft_putstr("\n\n");
	ft_display_esc();
	ft_putstr("\n\n");
	loop(cursor, var);
}
