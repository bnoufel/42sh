/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equalizer_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:01:15 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:02:43 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int			valid_cmp_int(char *str)
{
	if (!ft_strcmp(str, "-eq") || !ft_strcmp(str, "-ne")
		|| !ft_strcmp(str, "-gt") || !ft_strcmp(str, "-ge")
		|| !ft_strcmp(str, "-lt") || !ft_strcmp(str, "-le")
		|| !ft_strcmp(str, "!-eq") || !ft_strcmp(str, "!-ne")
		|| !ft_strcmp(str, "!-gt") || !ft_strcmp(str, "!-ge")
		|| !ft_strcmp(str, "!-lt") || !ft_strcmp(str, "!-le"))
		return (1);
	return (-10);
}

static int			valid_cmp(char *str, t_cmp *cmp)
{
	if (cmp->str_is_integer && cmp->str1_is_integer)
		return (valid_cmp_int(str));
	else if (!cmp->str_is_integer && !cmp->str1_is_integer)
	{
		if (!ft_strcmp(str, "=") || !ft_strcmp(str, "==")
			|| !ft_strcmp(str, "!=")
			|| !ft_strcmp(str, ">") || !ft_strcmp(str, "<")
			|| !ft_strcmp(str, "-n") || !ft_strcmp(str, "-z")
			|| !ft_strcmp(str, "-a") || !ft_strcmp(str, "-o")
			|| !ft_strcmp(str, "-nt")
			|| !ft_strcmp(str, "-ot") || !ft_strcmp(str, "-ef")
			|| !ft_strcmp(str, "!-n") || !ft_strcmp(str, "!-z")
			|| !ft_strcmp(str, "!-a") || !ft_strcmp(str, "!-o"))
			return (1);
		if (valid_cmp_int(str))
			return (-15);
		return (-10);
	}
	return (-11);
}

int					valid_cmp_before(char *str)
{
	if (!ft_strcmp(str, "-e") || !ft_strcmp(str, "-a")
		|| !ft_strcmp(str, "-f") || !ft_strcmp(str, "-s")
		|| !ft_strcmp(str, "-d") || !ft_strcmp(str, "-b")
		|| !ft_strcmp(str, "-c") || !ft_strcmp(str, "-p")
		|| !ft_strcmp(str, "-h") || !ft_strcmp(str, "-L")
		|| !ft_strcmp(str, "-S") || !ft_strcmp(str, "-t")
		|| !ft_strcmp(str, "-r") || !ft_strcmp(str, "-w")
		|| !ft_strcmp(str, "-x") || !ft_strcmp(str, "-g")
		|| !ft_strcmp(str, "-u") || !ft_strcmp(str, "-k")
		|| !ft_strcmp(str, "-O") || !ft_strcmp(str, "-G")
		|| !ft_strcmp(str, "-N"))
		return (1);
	return (-10);
}

int					init_struct_with_no_valid_cmp(t_cmp *cmp, char **str)
{
	int				ret;

	if (!(cmp->str = ft_strdup(str[1])))
		malloc_failed("init_struct");
	if (str[2] && (str[2][0] == '-' || str[2][0] == '!'))
	{
		if (!(cmp->cmp = ft_strdup(str[2])))
			malloc_failed("init_struct");
		if (!ft_strcmp(cmp->cmp, "!=") && (cmp->str1_is_integer
		|| cmp->str_is_integer))
			return (-16);
		ret = valid_cmp(str[2], cmp);
		if (ret < 1)
			return (ret);
	}
	else if (str[2] && !cmp->cmp)
		(!(cmp->cmp = ft_strdup(str[2]))) ? malloc_failed("init_struct") : 0;
	(!(cmp->str1 = ft_strdup(str[3]))) ? malloc_failed("init_struct") : 0;
	(!(cmp->end = ft_strdup(str[4]))) ? malloc_failed("init_struct") : 0;
	if ((!ft_strcmp(cmp->cmp, "=") || !ft_strcmp(cmp->cmp, "=="))
		&& (cmp->str1_is_integer || cmp->str_is_integer))
		return (-16);
	return (true);
}

int					init_struct_with_valid_cmp(t_cmp *cmp, char **str)
{
	cmp->str1 = NULL;
	if (str[1] && str[1][0] == '-')
	{
		if (str[1] && !(cmp->cmp = ft_strdup(str[1])))
			malloc_failed("init_struct_with_valid_cmp");
		(str[2] && !(cmp->str = ft_strdup(str[2]))) ? malloc_failed("cmp") : 0;
		(str[3] && !(cmp->end = ft_strdup(str[3]))) ? malloc_failed("cmp") : 0;
	}
	else if (str[1] && str[1][0] == '!' && ft_strlen(str[1]) > 1)
	{
		if (!(cmp->cmp = ft_strdup(str[1])))
			malloc_failed("init_struct_with_valid_cmp");
		return (-10);
	}
	else if (str[1] && str[2] && str[1][0] == '!' && str[2][0] == '-')
	{
		cmp->isnot = 1;
		if (str[2] && !(cmp->cmp = ft_strdup(str[2])))
			malloc_failed("init_struct_with_valid_cmp");
		if (str[3] && !(cmp->str = ft_strdup(str[3])))
			malloc_failed("init_struct_with_valid_cmp");
		if (str[4] && !(cmp->end = ft_strdup(str[4])))
			malloc_failed("init_struct_with_valid_cmp");
	}
	return (1);
}
