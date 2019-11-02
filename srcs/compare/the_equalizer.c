/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_equalizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:35 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/19 10:32:31 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

/*
** @brief ft_compare check a comparaison
** @param cur
** @param r
*/

void				ft_compare(t_par *cur, int *r)
{
	t_cmp			*cmp;
	char			**dest;
	t_av			*save;

	save = cur->lav;
	if (!(cmp = (t_cmp *)malloc(sizeof(t_cmp))))
		malloc_failed("ft_compare");
	dest = equalizer_core(cur);
	cur->lav = save;
	if ((cmp->error = init_struct(dest, cmp)) != 1)
		*r = 1;
	else if (((cmp->error = check_struct(cmp)) != 1) || !cmp->cmp)
		*r = 1;
	*r = the_equalizer(cmp) ? 0 : 1;
	if (cmp->error < 0)
	{
		*r = 1;
		the_equalizer_error(cmp);
	}
	ft_free_tab(dest);
	equalizer_free(cmp);
}
