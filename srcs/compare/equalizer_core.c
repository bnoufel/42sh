/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equalizer_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:08 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:09 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

/*
** @brief
** check_if_is_a_spec_file conditionnal jump s'il echoue
** @param cmp
** @return
*/

bool				the_equalizer(t_cmp *cmp)
{
	if (!cmp->str1)
	{
		if (check_file_exist(cmp))
			return (true);
		else if (check_if_is_a_spec_file(cmp))
			return (true);
		else if (check_if_file_no_empty(cmp))
			return (true);
		else if (check_file_right(cmp))
			return (true);
		else if (check_string_if_empty_null(cmp))
			return (true);
		return (false);
	}
	else
	{
		if (check_modification_file(cmp))
			return (true);
		else if (check_equalizer_int(cmp))
			return (true);
	}
	return (false);
}

/*
** @brief Si err = -13 faut relancer un read mais sinon je le protege
** @param cmp
** @return
*/

int					check_struct(t_cmp *cmp)
{
	if (!ft_strcmp(cmp->start, "[") && !ft_strcmp(cmp->end, "]]"))
		return (-12);
	if (!ft_strcmp(cmp->start, "[[") && !ft_strcmp(cmp->end, "]"))
		return (-13);
	if (cmp->str_is_integer && !cmp->str1_is_integer)
		return (-14);
	if (!cmp->str_is_integer && cmp->str1_is_integer)
		return (-15);
	return (1);
}

/*
** @brief initialise dest
** @param cur
** @return
*/

char				**equalizer_core(t_par *cur)
{
	char			**dest;
	int				i;

	i = 0;
	if (!(dest = (char **)malloc(sizeof(char *) * (cur->ac + 1))))
		malloc_failed("ft_compare");
	while (cur->lav)
	{
		if (!(dest[i++] = ft_strdup(cur->lav->av)))
			malloc_failed("ft_compare");
		cur->lav = cur->lav->next;
	}
	dest[i] = 0;
	return (dest);
}

/*
** @brief Free equalizer struct
** @param cmp
*/

void				equalizer_free(t_cmp *cmp)
{
	ft_strdel(&(cmp->start));
	ft_strdel(&(cmp->str1));
	ft_strdel(&(cmp->str));
	ft_strdel(&(cmp->cmp));
	ft_strdel(&(cmp->end));
	free(cmp);
	cmp = NULL;
}
