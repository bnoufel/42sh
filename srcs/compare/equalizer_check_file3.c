/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equalizer_check_file3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:59:59 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:39 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

/*
** @brief
** -ef : le file f1 et le file f2 sont des liens physiques vers le même file
** @param cmp
** @param f1
** @param f2
** @return
*/

static bool			check_modification_file2(t_cmp *cmp)
{
	char			*dest;
	t_stat			f1;
	t_stat			f2;

	if (!ft_strcmp(cmp->cmp, "-ef"))
	{
		if (stat(cmp->str, &f1) == -1 || stat(cmp->str1, &f2) == -1)
			return (false);
		if (!(dest = ft_strnew(256)))
			malloc_failed("check_modification_file");
		if (readlink(cmp->str1, dest, 256))
		{
			if (!ft_strcmp(dest, ft_return_home(cmp->str)))
			{
				free(dest);
				return (true);
			}
		}
		free(dest);
		return (false);
	}
	return (false);
}

/*
** @brief
** -nt : le fichier f1 est plus récent que le fichier f2
** -ot : le fichier f1 est plus ancien que le fichier f2
** @param cmp
** @param f1
** @param f2
** @return
*/

bool				check_modification_file(t_cmp *cmp)
{
	t_stat			f1;
	t_stat			f2;

	if (!ft_strcmp(cmp->cmp, "-nt"))
	{
		if (stat(cmp->str, &f1) == -1 || stat(cmp->str1, &f2) == -1)
			return (false);
		if (f1.st_ctime > f2.st_ctime)
			return (true);
	}
	else if (!ft_strcmp(cmp->cmp, "-ot"))
	{
		if (stat(cmp->str, &f1) == -1 || stat(cmp->str1, &f2) == -1)
			return (false);
		if (f1.st_ctime < f2.st_ctime)
			return (true);
	}
	else
		return (check_modification_file2(cmp));
	return (false);
}
