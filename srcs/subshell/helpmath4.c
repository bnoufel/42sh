/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmath4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:01:03 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:04 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	aroundmaths(char **tmp, char **s, char **s2, int *i)
{
	if (!(*tmp) && !(*s2))
	{
		ft_strlen(*s) >= 5 && (*s)[0] == '$' ? (*s)[0] = ' ' : 0;
		ft_strlen(*s) >= 5 && (*s)[ft_strlen(*s) - 2] == ')'
		? (*s)[ft_strlen(*s) - 2] = '\0' : 0;
	}
	else
	{
		ft_strdel(s);
		*s = ft_strjoin(*s2, (*tmp) + *i);
		ft_strdel(s2);
		ft_strdel(tmp);
	}
	*s2 = ft_strdup(*s);
	*tmp = ft_strrchr(*s2, 40);
	*tmp ? ((*tmp)[0] = '\0')
	: ((*s2)[0] = '\0');
	*i = 0;
}

void	endofmloop(char **tmp, int *c, int *i)
{
	!(*i) ? (*c = 2)
	: (*i = 1);
	if ((*tmp)[0] == 40)
	{
		(*tmp)[0] = ' ';
		while ((*tmp)[*i] && (*tmp)[*i] != 41)
			(*i)++;
		(*tmp)[*i] ? (*tmp)[*i] = ' ' : 0;
	}
	*i = 0;
	while ((*tmp)[*i] && ((*tmp)[*i] == ' ' || (*tmp)[*i] == '\t'))
		(*i)++;
}

int		finep1(char *s, int *i, int *c, int *j)
{
	if (*c > 0 || (ft_isdigit(s[*i]) && (!s[(*i) + 1]
	&& ft_isalpha(s[(*i) + 1]) && (!s[*i - 1] || isope(s + *i - 1)
	|| s[*i - 1] == ' ' || s[*i - 1] == '\t'))))
		return (-1);
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	if (ft_strlen(s + *i) >= 2 && (ft_strequ(s + *i, "++")
	|| ft_strequ(s + *i, "--")) && ((*i && !ft_isalpha(s[*i - 1]))
	|| !(*i)) && (s[*i + 2] && ft_isalpha(s[*i + 2])))
	{
		if ((*i > 2 && ((s[*i - 1] == '+' && s[*i - 2] == '+'
		&& s[*i - 3] != '+') || (s[*i - 1] == '-'
		&& s[*i - 2] == '-' && s[*i - 3] != '-')))
		|| (*i > 1 && ((s[*i - 1] == '+' && s[*i - 2] == '+')
		|| (s[*i - 1] == '-' && s[*i - 2] == '-'))))
			return (-1);
		(*i) += 2;
	}
	else
		return (finep2(s, i, c, j));
	return (0);
}

int		finep2(char *s, int *i, int *c, int *j)
{
	int	d;

	d = 0;
	if (ft_strlen(s + *i) >= 2 && (ft_strequ(s + *i, "++")
	|| ft_strequ(s + *i, "--")) && (*i && ft_isalpha(s[*i - 1]))
	&& (!s[*i + 2] || !ft_isalpha(s[*i + 2])))
		(*i) += 2;
	else if ((s[*i] == '+' || s[*i] == '-') && (*j = 1))
		(*i)++;
	else if (s[*i] != '+' && s[*i] != '-' && (*j = isope(s + *i)))
	{
		(*c)++;
		*i += *j;
	}
	else if (ft_isalnum(s[*i]) && (d = 1))
	{
		while (s[*i] && ft_isalnum(s[*i]))
			(*i)++;
		(*c)--;
	}
	else if (s[*i])
		return (-1);
	return (d);
}

int		calcul2(char *ope, long long l[3])
{
	if (*ope == '/' && ope[1] != '=')
	{
		if (!l[2])
			return (0);
		l[0] = l[1] / l[2];
	}
	else if (*ope == '+' && ope[1] != '=')
		l[0] = l[1] + l[2];
	else if (*ope == '%' && ope[1] != '=')
	{
		if (!l[2])
			return (0);
		l[0] = l[1] % l[2];
	}
	else if (*ope == '-' && ope[1] != '=')
		l[0] = l[1] - l[2];
	return (comparaison(ope, l));
}
