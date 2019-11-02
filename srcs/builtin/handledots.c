/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handledots.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:32:36 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:32:37 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void	singledot(int *t, int *i, int *l, char **s)
{
	char *af;

	if (*i + 3 < *l)
	{
		(af = ft_strdup(*s + *i + 3)) ? 0 : malloc_failed("sindledots");
		(*s)[*i + 1] = '\0';
		*s = substitute(*s, af);
	}
	else
		*i ? ((*s)[*i] = '\0')
		: ((*s)[*i + 1] = '\0');
	*t = 0;
	*i = 0;
}

static void	doubledots(int *t, int *i, int *l, char **s)
{
	char *af;

	if (*i + 4 < *l)
	{
		(af = ft_strdup(*s + *i + 4)) ? 0 : malloc_failed("doubledots");
		(*s)[*t + 1] = '\0';
		*s = substitute(*s, af);
		*l = (int)ft_strlen(*s);
	}
	else
		*t ? ((*s)[*t] = '\0')
		: ((*s)[*t + 1] = '\0');
	*t = 0;
	*i = 0;
}

void		handledots(char **s, int i, int t, int l)
{
	while ((*s)[i])
	{
		if ((*s)[i] == 47 && (*s)[i + 1] && (*s)[i + 1] != '.')
			t = i;
		if ((*s)[i] == 47 && (*s)[i + 1] && (*s)[i + 2] && (*s)[i + 1] == '.'
				&& (*s)[i + 2] == '.')
			doubledots(&t, &i, &l, s);
		else if ((*s)[i + 1] && (*s)[i] == 47 && (*s)[i + 1] == '.'
		&& (!((*s)[i + 2]) || (*s)[i + 2] == 47))
			singledot(&t, &i, &l, s);
		i++;
	}
}
