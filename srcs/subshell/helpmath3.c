/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmath3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:01:02 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:02 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char			*trncat(char *tr, char *s)
{
	int			i;
	int			j;
	int			m;

	i = 0;
	j = 0;
	m = 0;
	while (s && s[i] && (s[i] == ' ' || s[i] == '+' || s[i] == '-'))
	{
		s[i] == '-' ? m++ : 0;
		i++;
	}
	(m % 2) ? tr[j++] = '-' : 0;
	while (s && ft_isalnum(s[i]))
		tr[j++] = s[i++];
	tr[j] = '\0';
	return (tr);
}

char			*cleans(char *s, char **s2)
{
	char		*t;
	int			i;

	i = (s[0] && s[0] == ' ') ? 1 : 0;
	while (s[i] && s[i] == 40)
		i++;
	if ((s + i)[0])
	{
		(t = ft_strdup(s + i)) ? 0 : malloc_failed("cleans");
		trncat(t, s + i);
	}
	else
		(t = ft_strdup("0")) ? 0 : malloc_failed("cleans");
	ft_strdel(&s);
	ft_strdel(s2);
	return (t);
}

void			isvar(char **s, t_var *var, t_par *par, int *a)
{
	char		c;
	int			i;
	char		*v;
	char		tr[LINE_MAX];

	i = -1;
	c = 0;
	while ((*s)[++i])
	{
		if (ft_isalpha((*s)[i]) && ((*a) += 1) && (v = trncat(tr, (*s) + i)))
		{
			(i > 1 && (((*s)[i - 1] == '+' && (*s)[i - 2] == '+')
			|| ((*s)[i - 1] == '-' && (*s)[i - 2] == '-')))
			? incremvar(tr, var, (*s)[i - 1], par) : 0;
			var && !(v = retenv(var->lenv, tr)) ?
				(v = retenv(var->loc, tr)) : 0;
			c = (*s)[i + ft_strlen(tr)];
			(c == '+' || c == '-') && (*s)[i + ft_strlen(tr) + 1] == c
				? incremvar(tr, var, c, par) : 0;
			(*s)[i] = '\0';
			*s = v ? mathcore(substitute(*s, ft_strdup(v)), var, par)
				: mathcore(substitute(*s, ft_strdup("0")), var, par);
			i = v ? i : 0;
		}
	}
}

char			*mathabort(char **s, char **tmp)
{
	char		*str;

	write(2, "mysh: bad math expression\n", 26);
	g_global->ret = 1;
	ft_strdel(tmp);
	ft_strdel(s);
	if (!(str = ft_strnew(0)))
		malloc_failed("mathabort");
	return (str);
}

void			helptosub(char **s, int *i, t_par *par, t_var *var)
{
	int			j;
	int			n;
	char		tr[LINE_MAX];
	char		*tmp;
	char		*last;

	n = 0;
	(!(tmp = ft_strnew(0))) ? malloc_failed("helptosub") : 0;
	if ((*s)[*i + 1] == 40 && (*i)++)
		helpbrackets(s, i, &par, &var);
	else if ((*s)[*i + 1] == '$')
	{
		(!(last = ft_strdup((*s) + *i + 2))) ? malloc_failed("helptosub") : 0;
		(*s)[*i] = '\0';
		*s = substitute(*s, substitute(lltoa(getpid()), last));
	}
	else
	{
		j = *i;
		if (cpu(tr, *s, &j) && wstruct(var, &tmp, &n, tr))
			(!(tmp = ft_strdup("0"))) ? malloc_failed("helptosub") : 0;
		(!(last = ft_strdup((*s) + j))) ? malloc_failed("helptosub") : 0;
		(*s)[*i] = '\0';
		*s = substitute(*s, substitute(tmp, last));
	}
}
