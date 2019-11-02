/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equalizer_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:13 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:14 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void			check_string(const char *str, const char *str1, t_cmp *cmp)
{
	int				i;

	i = (str[0] == '-' || str[0] == '+') ? 0 : -1;
	while (str[++i])
	{
		if ((str[i] >= '0' && str[i] <= '9'))
			cmp->str_is_integer = true;
		else
		{
			cmp->str_is_integer = false;
			break ;
		}
	}
	i = (str[0] == '-' || str[0] == '+') ? 0 : -1;
	while (str1[++i])
	{
		if ((str1[i] >= '0' && str1[i] <= '9'))
			cmp->str1_is_integer = true;
		else
		{
			cmp->str1_is_integer = false;
			break ;
		}
	}
}

static void			init_equalizer(t_cmp **cmp)
{
	(*cmp)->isnot = -1;
	(*cmp)->str_is_integer = false;
	(*cmp)->str1_is_integer = false;
	(*cmp)->error = 0;
	(*cmp)->start = NULL;
	(*cmp)->str = NULL;
	(*cmp)->str1 = NULL;
	(*cmp)->cmp = NULL;
	(*cmp)->end = NULL;
}

int					init_struct(char **str, t_cmp *cmp)
{
	init_equalizer(&cmp);
	if (!str[0] || !str[ft_sstrlen(str) - 1] || str[0][0] != '['
	|| str[ft_sstrlen(str) - 1][0] != ']')
		return (-12);
	if (!(cmp->start = ft_strdup(str[0])))
		malloc_failed("init_struct: dup start");
	if (str[1] && str[1][0] == '-'
			&& (cmp->error = valid_cmp_before(str[1])) > 0)
		cmp->error = init_struct_with_valid_cmp(cmp, str);
	else if (str[1] && str[1][0] == '!'
			&& (cmp->error = valid_cmp_before(str[2])) > 0)
		cmp->error = init_struct_with_valid_cmp(cmp, str);
	else if (ft_sstrlen(str) == 5)
	{
		check_string(str[1], str[3], cmp);
		return (init_struct_with_no_valid_cmp(cmp, str));
	}
	if (cmp->error < 0)
		return (cmp->error);
	return (1);
}
