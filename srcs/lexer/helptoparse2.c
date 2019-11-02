/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helptoparse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:39:22 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:39:23 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		newbuf(char *buf, int *brk, t_par **cur)
{
	int		i;

	i = ft_strlen((*cur)->action) ? (int)ft_strlen((*cur)->action) : 1;
	while (buf[i] && (buf[i] == ' ' || buf[i] == '\t'))
		i++;
	!(*buf) ? *brk = 1 : 0;
	return (i);
}

void	cleanbrk(t_par **cur, t_par **tmp, char *buf, int brk)
{
	if (brk && *buf && ((*cur)->lav || (*cur)->action[0]))
	{
		*tmp = *cur;
		*cur = (*cur)->next;
		*cur = newelem(*tmp);
		(*tmp)->next = *cur;
	}
}

int		onec(int *brk, char *s, t_par *par)
{
	int	i;

	i = 0;
	if (!g_global->par && (s[i] == ';'
	|| s[i] == '|' || s[i] == '<' || s[i] == '>'))
	{
		(s[i] != ';' || (s[i + 1] && s[i + 1] == ';'))
			? ft_strncpy(par->action, s + i, 1) : 0;
		*brk = 1;
		return (1);
	}
	else if (s[i] == ' ' || s[i] == '\t')
	{
		*brk = 0;
		return (1);
	}
	else if (!g_global->par && s[i] == '&' && s[i + 1] != '<'
	&& s[i + 1] != '>')
	{
		*brk = 1;
		par->bg = 1;
		return (1);
	}
	return (0);
}

int		digit(int *brk, char *s, t_par *par)
{
	int i;
	int a;
	int c;

	i = 0;
	a = i;
	if (s && ft_isdigit(s[i]))
	{
		a = i;
		while (s[i] && (ft_isdigit(s[i]) || s[i] == '&'))
		{
			i++;
			if (s[i] == '>' || s[i] == '<')
			{
				i += (s[i + 1] && s[i + 1] == '&') ? 2 : 1;
				ft_atoc(s + a, &c);
				(s[i - 1] == '&' && !c) || s[i - 1] != '&'
					? ft_strncpy(par->action, s + a, i - a) : 0;
				s[i - 1] == '&' && c < 0 ? ft_strcpy(par->action, "+") : 0;
				*brk = 1;
				return (1);
			}
		}
	}
	return (0);
}

int		isbkslsh(char **s, int *i)
{
	int		l;
	char	*t;
	int		a;

	while ((*s)[*i] == 92 && (*s)[(*i) + 1] && (*s)[(*i) + 2])
		*i = (*i) + 2;
	a = *i;
	while ((*s)[*i] == 92)
	{
		t = (*i == a) ? ft_strdup(*s) : NULL;
		t ? (t[ft_strlen(t) - 2] = '\0') : 0;
		l = (int)ft_strlen(*s);
		ft_mini_read(s, i, 2, ' ');
		ft_cursorless();
		t = substitute(t, ft_strdup(*s + l));
		ft_strdel(s);
		*s = t;
		(*i) = a;
		if ((*s)[*i] != 92 || (*s)[*i + 1] != ' ')
		{
			(*s)[*i] == 92 ? (*i)++ : 0;
			return (1);
		}
	}
	return (0);
}
