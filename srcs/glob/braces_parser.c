/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:34:25 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:34:27 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static bool		braces_check_arg(t_braces *braces)
{
	braces->is_good = 0;
	braces->is_num = 0;
	if (number_braces_valid(braces->str[0])
	&& number_braces_valid(braces->str[1]))
	{
		braces->is_good = 1;
		braces->is_num = 1;
	}
	else if (braces->str[0][0] >= 32 && braces->str[1][0] <= 126
	&& !braces->str[0][1] && !braces->str[1][1])
		braces->is_good = 1;
	return (braces->is_good ? true : false);
}

static int		check_braces(t_braces *braces, char **core)
{
	braces->is_good = 0;
	braces->is_num = 0;
	if (!(braces->str = (char **)malloc(sizeof(char *) * 3)))
		malloc_failed("check_braces");
	braces->str[0] = core ? bckslshav(core[0], 0) : 0;
	braces->str[1] = core ? bckslshav(core[1], 0) : 0;
	braces->str[2] = 0;
	if (!(braces_check_arg(braces)))
	{
		ft_free_tab(braces->str);
		return (-41);
	}
	if (!braces->str || !braces->str[0] || !braces->str[1])
		return (-42);
	return (1);
}

char			*braces_parser(char **str, int *j)
{
	t_split		split;
	t_braces	braces;
	int			ret;
	char		*to_ret;
	char		**core;

	if (!(split_folder_braces(&split, *str, &core)))
		return (NULL);
	ret = check_braces(&braces, core);
	ft_free_tab(core);
	if (ret == 0 || ret == -41 || ret == -42 || !braces.is_good
	|| !(to_ret = braces_bind(&split, &braces, j)))
	{
		free_struct_folder(&split);
		if (ret != -41)
			ft_free_tab(braces.str);
		*j = 0;
		return (*str);
	}
	free_struct_folder(&split);
	ft_strdel(str);
	return (*str = to_ret);
}
