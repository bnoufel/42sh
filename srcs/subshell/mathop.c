/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:01:12 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:12 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				isope(char *s)
{
	int	r;

	if ((r = bwise(s))
	|| (r = fope(s))
	|| (r = sope(s))
	|| (r = tope(s))
	|| (r = fthope(s))
	|| (r = sthope(s))
	|| (r = lope(s)))
		return (r);
	return (0);
}

char			*writeresult(long long r, char **s, int j)
{
	char	*a;
	char	*b;
	char	tmp[LINE_MAX];
	char	tmp2[LINE_MAX];
	int		i;

	i = 0;
	a = beforeop(*s, j - 1);
	b = afterop((*s) + j);
	ft_strcpy(tmp, b);
	*a = '\0';
	ft_strcpy(tmp2, *s);
	while (tmp[i] == '+' || tmp[i] == '-')
		i++;
	while (tmp[i] && tmp[i] != ' ' && tmp[i] != '\t' && tmp[i] != 41
	&& !(isope(tmp + i)))
		i++;
	a = lltoa(r);
	b = ft_strjoin(a, tmp + i);
	ft_strdel(&a);
	ft_strdel(s);
	return (*s = lastcheck(tmp2, b));
}

char			*mathaction(char **s, int i, t_var *var, t_par *par)
{
	long long	l[3];
	char		tr[LINE_MAX];

	par->br = 0;
	l[1] = mact(*s, i, var, par);
	par->br = 1;
	if ((!(l[2] = mact(*s, i, var, par)) && !(trncat(tr, afterop((*s) + i))[0]))
	|| !assignation((*s) + i, l, beforeop(*s, i - 1), var))
		return (0);
	return (writeresult(l[0], s, i));
}

int				isstrfine(char **s)
{
	int		i;
	int		j;
	int		c;
	int		d;

	i = (*s)[0] == 40 ? 1 : 0;
	j = 0;
	c = 0;
	if (fine(*s, i, c, j) == -1)
		return (0);
	while ((*s)[i] && (*s)[i] != 41)
	{
		if ((d = finep1(*s, &i, &c, &j)) == -1)
			return (0);
		j = 0;
	}
	return (c > 0 || (!j && !c && !d) ? 0 : 1);
}

char			*mathcore(char *s, t_var *var, t_par *par)
{
	char		*s2;
	char		*tmp;
	int			i;
	int			c;

	c = 0;
	tmp = NULL;
	s2 = NULL;
	i = 0;
	aroundmaths(&tmp, &s, &s2, &i);
	while (c != 2 && subinmath(&s, par, var) && ((ft_strrchr(s, 40)
	&& (tmp = ft_strdup(ft_strrchr(s, 40))))
	|| (tmp = ft_strdup(s))))
	{
		if (((i += vfope(&tmp, &c)) && c == 2) || !isstrfine(&tmp)
		|| ((i += (c = chooseop(&tmp, var, par))) && c == 2))
			return (mathabort(&s, &tmp));
		isvar(&tmp, var, par, &i);
		endofmloop(&tmp, &c, &i);
		aroundmaths(&tmp, &s, &s2, &i);
	}
	s = cleans(s, &s2);
	g_global->ret = ft_atoc(s, &c) ? 0 : 1;
	return (s);
}
