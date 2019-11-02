/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_braces2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:34:20 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:34:21 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void		braces_bind_num_min(char **ret, int min, int max, t_split *spl)
{
	if (min < 0 && g_global->prefix)
	{
		if (!(*ret = ft_strdup("-- ")))
			malloc_failed("braces_bind_number");
	}
	while (min <= max)
	{
		if (spl->before && !(*ret = ft_strjoinfree(*ret, spl->before, 1)))
			malloc_failed("braces_bind_number");
		if (!(*ret = substitute(*ret, lltoa(min))))
			malloc_failed("braces_bind_number");
		if (spl->after && !(*ret = ft_strjoinfree(*ret, spl->after, 1)))
			malloc_failed("braces_bind_number");
		if (min + 1 <= max && !(*ret = ft_strjoinfree(*ret, " ", 1)))
			malloc_failed("braces_bind_number");
		min++;
	}
}

static void		braces_bind_num_max(char **ret, int min, int max, t_split *spl)
{
	if (max < 0 && g_global->prefix)
	{
		if (!(*ret = ft_strdup("-- ")))
			malloc_failed("braces_bind_number");
	}
	while (min >= max)
	{
		if (spl->before && !(*ret = ft_strjoinfree(*ret, spl->before, 1)))
			malloc_failed("braces_bind_number");
		if (!(*ret = substitute(*ret, lltoa(min))))
			malloc_failed("braces_bind_number");
		if (spl->after && !(*ret = ft_strjoinfree(*ret, spl->after, 1)))
			malloc_failed("braces_bind_number");
		if (min - 1 >= max && !(*ret = ft_strjoinfree(*ret, " ", 1)))
			malloc_failed("braces_bind_number");
		min--;
	}
}

void			braces_bind_number(char **ret, int min, int max, t_split *spl)
{
	if (min <= max)
		braces_bind_num_min(ret, min, max, spl);
	else
		braces_bind_num_max(ret, min, max, spl);
}

int				diff_min_max(int min, int max)
{
	int			len;

	len = 0;
	len += (min < 0 || max < 0) ? 2 : 0;
	if (min <= max)
	{
		while (min <= max)
		{
			len++;
			min++;
		}
	}
	else
	{
		while (max <= min)
		{
			len++;
			max++;
		}
	}
	return (len + 1);
}

char			*braces_bind(t_split *split, t_braces *braces, int *recu)
{
	char		*ret;

	if (braces->is_num)
	{
		if (!(ret = braces_cat_number(split, braces->str)))
			return (NULL);
	}
	else
	{
		if (!(ret = braces_cat_letter(split, braces->str)))
			return (NULL);
	}
	*recu = 1;
	return (ret);
}
