/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equalizer_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:10 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:12 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char				*the_equalizer_error3(t_cmp *cmp)
{
	char				*err;

	err = NULL;
	if (cmp->error == -16)
	{
		if (!(err = ft_strdup(
			"mysh: parse error: condition unexpected: ")))
			malloc_failed("ft_equalizer_error");
	}
	else if (cmp->error == -17)
	{
		if (!(err = ft_strdup("mysh: [: too many arguments")))
			malloc_failed("ft_equalizer_error");
	}
	else if (cmp->error == -20)
	{
		if (!(err = ft_strdup("mysh: [: unknown error")))
			malloc_failed("ft_equalizer_error");
	}
	return (err);
}

static char				*the_equalizer_error2(t_cmp *cmp)
{
	char				*err;

	err = NULL;
	if (cmp->error == -13)
	{
		if (!(err = ft_strjoin("mysh: [: expected : ']]' got: ", cmp->end)))
			malloc_failed("ft_equalizer_error");
	}
	else if (cmp->error == -14)
	{
		if (!(err = ft_strjoin(
			"mysh: [: integer expression expected: ", cmp->str1)))
			malloc_failed("ft_equalizer_error");
	}
	else if (cmp->error == -15)
	{
		if (!(err = ft_strjoin(
			"mysh: [: integer expression expected: ", cmp->str)))
			malloc_failed("ft_equalizer_error");
	}
	else
		return (the_equalizer_error3(cmp));
	return (err);
}

void					the_equalizer_error(t_cmp *cmp)
{
	char				*err;

	err = NULL;
	if (cmp->error == -10)
	{
		if (!(err = ft_strjoin("mysh: [: unknown condition: ", cmp->cmp)))
			malloc_failed("ft_equalizer_error");
	}
	else if (cmp->error == -11)
	{
		if (!(err = ft_strjoin(
			"mysh: parse error: condition expected: ", cmp->str)))
			malloc_failed("ft_equalizer_error");
	}
	else if (cmp->error == -12)
	{
		if (!(err = ft_strdup("mysh: [: ']' expected")))
			malloc_failed("ft_equalizer_error");
	}
	else
		err = the_equalizer_error2(cmp);
	ft_putendl(err);
	free(err);
}
