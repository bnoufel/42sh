/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:56 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:57 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			vfope(char **s, int *c)
{
	int i;

	i = 0;
	*c = 0;
	while ((*s)[i])
	{
		if ((ft_strlen((*s) + i) >= 2 && ft_strequ((*s) + i, "0x")
		&& ((*s)[i - 1] == ' ' || (*s)[i - 1] == '\t'
		|| (*s)[i - 1] == 40 || isope((*s) + i - 1)))
		|| (ft_isdigit((*s)[i]) && (*s)[i + 1] == '#'))
		{
			if (!conversion(s, i))
				return (2);
			*c = 1;
			i = 0;
		}
		i++;
	}
	return (*c);
}

static int	used(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	else if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	return (0);
}

long long	convertbase(char *s, int base)
{
	int			i;
	long long	nb;
	long long	pow;
	int			neg;

	i = 0;
	neg = 1;
	nb = 0;
	pow = ft_iterative_power(base, (ft_strlen(s) - 1));
	neg = (s[i] == '-') ? -1 : 1;
	(s[i] == '-' || s[i] == '+') ? i++ : 0;
	while (pow > 1)
	{
		nb += used(s[i++]) * pow;
		pow /= base;
	}
	nb += used(s[i]);
	nb *= neg;
	return (nb);
}

static int	convp2(char **s, int a, long long *r)
{
	char	aa[LINE_MAX];
	int		b;
	int		i;

	i = 0;
	trncat(aa, beforeop((*s), a));
	b = ft_atoc(aa, &i);
	i = (int)ft_strlen(aa);
	if (b < 2 || b > 36)
		return (0);
	while (((*s) + a)[i] && ft_isalnum(((*s) + a)[i]))
	{
		if ((((*s) + a)[i] < '0' || ((*s) + a)[i] > '9')
		&& (((*s) + a)[i] < 'a' || ((*s) + a)[i] > 'a' - 10 + a)
		&& (((*s) + a)[i] < 'A' || ((*s) + a)[i] > 'A' - 10 + a))
			return (0);
		i++;
	}
	trncat(aa, (*s) + a + 2);
	*r = convertbase(aa, b);
	return (1);
}

char		*conversion(char **s, int a)
{
	int			i;
	char		aa[LINE_MAX];
	long long	r;

	i = 0;
	if (ft_strlen((*s) + a) >= 2 && ft_strequ((*s) + a, "0x"))
	{
		i = 2;
		while (((*s) + a)[i] && ft_isalnum(((*s) + a)[i]))
		{
			if ((((*s) + a)[i] < '0' || ((*s) + a)[i] > '9')
					&& (((*s) + a)[i] < 'a' || ((*s) + a)[i] > 'f')
					&& (((*s) + a)[i] < 'A' || ((*s) + a)[i] > 'F'))
				return (0);
			i++;
		}
		trncat(aa, (*s) + a + 2);
		r = convertbase(aa, 16);
	}
	else if (!convp2(s, a, &r))
		return (0);
	writeresult(r, s, a);
	return (*s);
}
