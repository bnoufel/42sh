/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_braces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:34:14 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:34:15 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char			*braces_cat_number(t_split *split, char **core)
{
	char		*ret;
	long		min;
	long		max;
	long		diff;

	ret = NULL;
	if ((!check_is_valid_number(core[0], core[1])) && ft_free_tab(core))
		return (NULL);
	min = ft_atol(core[0]);
	max = ft_atol(core[1]);
	if (!(check_max(min, max, &diff)))
	{
		ft_putendl_fd("parse error", 2);
		return (NULL);
	}
	braces_bind_number(&ret, min, max, split);
	ft_free_tab(core);
	return (ret);
}

static void		join_letter_min(char **ret, char min, char max, t_split *split)
{
	while (min <= max)
	{
		if (split->before && !(*ret = ft_strjoinfree(*ret, split->before, 1)))
			malloc_failed("join_letter_min");
		if (!(*ret = substitute(*ret, ft_chardup_spec(min))))
			malloc_failed("join_letter_min");
		if (split->after && !(*ret = ft_strjoinfree(*ret, split->after, 1)))
			malloc_failed("join_letter_min");
		if (min + 1 <= max && !(*ret = ft_strjoinfree(*ret, " ", 1)))
			malloc_failed("join_letter_min");
		min++;
	}
}

static void		join_letter_max(char **ret, char min, char max, t_split *split)
{
	while (min >= max)
	{
		if (split->before && !(*ret = ft_strjoinfree(*ret, split->before, 1)))
			malloc_failed("join_letter_max");
		if (!(*ret = substitute(*ret, ft_chardup_spec(min))))
			malloc_failed("join_letter_max");
		if (split->after && !(*ret = ft_strjoinfree(*ret, split->after, 1)))
			malloc_failed("join_letter_max");
		if (min - 1 >= max && !(*ret = ft_strjoinfree(*ret, " ", 1)))
			malloc_failed("join_letter_max");
		min--;
	}
}

static void		braces_bind_letter(char **ret, char min, char max, t_split *sp)
{
	if (min <= max)
		join_letter_min(ret, min, max, sp);
	else
		join_letter_max(ret, min, max, sp);
}

char			*braces_cat_letter(t_split *split, char **core)
{
	char		*ret;
	char		min;
	char		max;

	ret = NULL;
	min = core[0][0];
	max = core[1][0];
	braces_bind_letter(&ret, min, max, split);
	ft_free_tab(core);
	return (ret);
}
