/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helptoparse3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:39:29 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:39:30 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		checkpid(void)
{
	while (g_global->pid)
	{
		if (g_global->pid->pid == getpid())
			return (1);
		g_global->pid = g_global->pid->next;
	}
	return (0);
}

int		helpbrackets2(char **s, int *i, t_par *par)
{
	par ? par->math = 0 : 0;
	par ? par->br = 0 : 0;
	if (!(*i = brackets(s, *i, par, 0)))
		return (0);
	return (1);
}

int		helpbrackets(char **s, int *i, t_par **par, t_var **var)
{
	int		a;
	char	*middle;
	char	*last;
	int		r;

	r = 0;
	a = *i;
	if (!helpbrackets2(s, i, *par))
		return (0);
	if (a && (*s)[a - 1] == '$' && (*s)[a] == 40)
	{
		last = ft_strdup((*s) + (*i) + 1);
		middle = ft_strdup((*s) + a - 1);
		middle[*i + 1 - a] = ' ';
		middle[*i + 2 - a] = '\0';
		(*s)[a - 1] = '\0';
		*s = (*par)->math
		? substitute(*s, substitute(mathcore(middle, *var, *par), last))
		: substitute(*s, substitute(parse_subshell(middle, var, (*par)->q),
		last));
		*i = a - 1;
	}
	(*par)->q = 0;
	return (1);
}

int		helpquotes(char **s, int *i, t_par *par, t_var **var)
{
	int		a;
	char	*middle;
	char	*last;
	int		r;

	r = 0;
	a = *i;
	if (!(*i = skipquotes(s, *i, par, 0)))
		return (0);
	if ((*s)[a] == 96)
	{
		if (!(last = ft_strdup((*s) + *i + 1)))
			malloc_failed("helppquotes");
		if (!(middle = ft_strdup((*s) + a)))
			malloc_failed("helppquotes");
		middle[*i - a] = ' ';
		middle[*i + 1 - a] = '\0';
		(*s)[a] = '\0';
		*s = substitute(*s, substitute(parse_subshell(middle, var, par->q)
		, last));
		*i = a;
		par->q = 0;
	}
	return (1);
}

char	wdelim(char *s, int *i, t_par *cur)
{
	static int	a;
	char		c;

	c = 0;
	if (s[*i] == 40 && (c = 41))
	{
		if (cur)
		{
			if (!cur->br)
				a = *i;
			else if (cur->br == 1 && *i == a + 1)
				cur->math = 1;
			cur->br++;
		}
	}
	else if (s[*i] == 123)
		c = 125;
	else if (s[*i] == 34)
		c = 34;
	else if (s[*i] == 39)
		c = 39;
	else if (s[*i] == 96)
		c = 96;
	(*i)++;
	return (c);
}
