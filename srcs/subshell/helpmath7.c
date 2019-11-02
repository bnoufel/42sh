/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmath7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:01:11 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:11 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		fine(char *s, int i, int c, int j)
{
	while (s[i] && s[i] != 41)
	{
		if (!j && (s[i] == '+' || s[i] == '-'))
			i++;
		if (isope(s + i))
			c = 1;
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i] && ft_isalnum(s[i]) && !isope(s + i))
			j++;
		while (s[i] && ft_isalnum(s[i]) && !isope(s + i))
			i++;
		if (!j && (s[i] == '+' || s[i] == '-'))
			i++;
		if (isope(s + i))
			c = 1;
		s[i] ? i++ : 0;
	}
	if (!c && j > 1)
		return (-1);
	return (1);
}

char	*lastcheck(char *a, char *b)
{
	int		i;
	char	*ret;

	i = 0;
	while (a[i])
	{
		if (isope(a + i))
		{
			ret = ft_strjoin(a, b);
			ft_strdel(&b);
			return (ret);
		}
		i++;
	}
	if (!i || a[i - 1] == '(')
	{
		ret = ft_strjoin(a, b);
		ft_strdel(&b);
		return (ret);
	}
	return (mathabort(NULL, &b));
}

int		bwise(char *s)
{
	if ((*s == '^' || (s[0] == '|' && s[1] != '|')
				|| (s[0] == '&' && s[1] != '&')) && s[1] != '=')
		return (1);
	else if (ft_strlen(s) >= 2 && (ft_strequ(s, "<<") || ft_strequ(s, ">>"))
			&& s[2] != '=')
		return (2);
	return (0);
}

int		lope(char *s)
{
	int i;

	i = 0;
	if (ft_strlen(s) >= 3 && (ft_strequ(s, "<<=") || ft_strequ(s, ">>=")))
		return (3);
	else if (ft_strlen(s) >= 2 && (ft_strequ(s, "&=") || ft_strequ(s, "*=")
	|| ft_strequ(s, "+=") || ft_strequ(s, "-=") || ft_strequ(s, "^=")
	|| ft_strequ(s, "/=") || ft_strequ(s, "%=")))
		return (2);
	else if (*s == '=' && s[1] != '=')
		return (1);
	return (0);
}
