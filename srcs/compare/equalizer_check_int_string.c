/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equalizer_check_int_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:06 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:07 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

/*
** @brief
** -eq & = & == : est égal à
** -ne & !-eq : n'est pas égal à
** -gt & !-lt & > : est plus grand que
** -lt & !gt & < : est plus petit que
** -ge & !-le : est plus grand ou égal à
** -le & !-ge : est plus petit ou égal à
** @param cmp
** @param s1
** @param s2
** @return
*/

static bool			check_equalizer_compare_int(t_cmp *cmp, int s1, int s2)
{
	if ((!ft_strcmp(cmp->cmp, "-eq")
	|| !ft_strcmp(cmp->cmp, "==") || !ft_strcmp(cmp->cmp, "=")) && s1 == s2)
		return (true);
	else if ((!ft_strcmp(cmp->cmp, "!-eq")
	|| !ft_strcmp(cmp->cmp, "!=")) && s1 != s2)
		return (true);
	else if (!ft_strcmp(cmp->cmp, "-ne") && s1 != s2)
		return (true);
	else if (!ft_strcmp(cmp->cmp, "!-ne") && s1 == s2)
		return (true);
	else if ((!ft_strcmp(cmp->cmp, "-gt")
	|| !ft_strcmp(cmp->cmp, "!-lt") || !ft_strcmp(cmp->cmp, ">")) && s1 > s2)
		return (true);
	else if ((!ft_strcmp(cmp->cmp, "!-gt")
	|| !ft_strcmp(cmp->cmp, "-lt") || !ft_strcmp(cmp->cmp, "<")) && s1 < s2)
		return (true);
	else if ((!ft_strcmp(cmp->cmp, "-ge")
	|| !ft_strcmp(cmp->cmp, "!-le")) && s1 >= s2)
		return (true);
	else if ((!ft_strcmp(cmp->cmp, "!-ge")
	|| !ft_strcmp(cmp->cmp, "-le")) && s1 <= s2)
		return (true);
	return (false);
}

/*
** @brief
** -a : et logique
** !-a : ! et logique
** -o : ou logique
** !-o : ! ou logique
** @param cmp
** @return
*/

bool				check_operator(t_cmp *cmp)
{
	if (!ft_strcmp(cmp->cmp, "-a"))
		return (cmp->str && cmp->str1);
	else if (!ft_strcmp(cmp->cmp, "!-a"))
		return (!(cmp->str && cmp->str1));
	else if (!ft_strcmp(cmp->cmp, "-o"))
		return (cmp->str || cmp->str1);
	else if (!ft_strcmp(cmp->cmp, "!-o"))
		return (!(cmp->str || cmp->str1));
	return (false);
}

/*
** @brief
** -n & !-z : la chaîne de caractères n'est pas « vide ».
** -z & !-n : la chaîne de caractères est « vide ».
** @param cmp
** @return
*/

bool				check_string_if_empty_null(t_cmp *cmp)
{
	if (!ft_strcmp(cmp->cmp, "-n") || !ft_strcmp(cmp->cmp, "!-z"))
	{
		if (cmp->str)
			return (true);
	}
	else if (!ft_strcmp(cmp->cmp, "!-n") || !ft_strcmp(cmp->cmp, "-z"))
	{
		if (!cmp->str)
			return (true);
	}
	return (false);
}

/*
** @brief RTFM
** @param cmp
** @return
*/

bool				check_equalizer_int(t_cmp *cmp)
{
	int				s1;
	int				s2;

	if (!cmp->str_is_integer && !cmp->str1_is_integer)
	{
		if (!ft_strcmp(cmp->cmp, "=") || !ft_strcmp(cmp->cmp, "=="))
		{
			if (!ft_strcmp(cmp->str, cmp->str1))
				return (true);
		}
		return (false);
	}
	s1 = ft_atoi(cmp->str);
	s2 = ft_atoi(cmp->str1);
	if (check_equalizer_compare_int(cmp, s1, s2))
		return (true);
	else if (check_operator(cmp))
		return (true);
	return (false);
}
