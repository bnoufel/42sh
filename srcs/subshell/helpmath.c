/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:59 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:00 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char	*beforeop(char *s, int i)
{
	while (i && (s[i] == ' ' || s[i] == '\t'))
		i--;
	while (i && s[i] != ' ' && s[i] != '\t' && s[i] != 40)
	{
		if (i && (s[i] == '+' || s[i] == '-'))
		{
			if (ft_isalnum(s[i - 1]))
				return (s + i);
			i--;
		}
		if (i && !isope(s + i))
			i--;
		else
		{
			i++;
			break ;
		}
	}
	return (s[i] == 40 ? s + i + 1 : s + i);
}

char	*afterop(char *s)
{
	int	i;

	i = isope(s);
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	return (s + i);
}

int		incremvar(char *s, t_var *var, char c, t_par *par)
{
	char	*v;
	char	t[LINE_MAX];

	if (!(v = retenv(var->lenv, s))
	&& !(v = retenv(var->loc, s)))
	{
		c == '+' ? ft_strcat(ft_strcpy(t, s), "=1") :
			ft_strcat(ft_strcpy(t, s), "=-1");
		helpchkivar(0, 0, &var, t);
	}
	else if (c == '+')
		helpinvar(v, '+', var, par);
	else if (c == '-')
		helpinvar(v, '-', var, par);
	return (1);
}

int		chooseop(char **s, t_var *var, t_par *par)
{
	int		c;
	int		i;
	int		op;
	int		(*ope)(char *);

	i = 0;
	op = 1;
	c = 0;
	while (wop(op, &ope))
	{
		if (op == 4 && !i)
			while ((*s)[i] && ((*s)[i] == '+' || (*s)[i] == '-'))
				i++;
		if ((*s)[i] && ope((*s) + i))
		{
			if (!mathaction(s, i, var, par))
				return (2);
			i = 0;
			c = 1;
		}
		i = (*s)[i] ? i + 1 : 0;
		op = (*s)[i] ? op : op + 1;
	}
	return (c);
}

int		ckop(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != 40)
	{
		if (s[i] != '-' && s[i] != '+' && isope(s + i))
			return (0);
		if (ft_isalnum(s[i]))
			return (1);
		i--;
	}
	return (0);
}
