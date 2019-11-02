/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpenv3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:33:20 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:33:21 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		nopwdcase(t_env **tmp, t_env **head, int a)
{
	t_env *env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		malloc_failed("copyenv");
	env->next = NULL;
	!a ? *head = env : 0;
	*tmp ? (*tmp)->next = env : 0;
	ft_strcpy(ft_strcpy(env->elem, "PWD=") + 4, g_global->spwd->pwd);
	*tmp = env;
	env = env->next;
}

char		chardelim(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if ((s[i] == 34 || s[i] == 39) && (!i || !nbcks(s, i - 1)))
			return (s[i]);
		i++;
	}
	return (0);
}

int			cpu(char *d, char *s, int *i)
{
	int	a;
	int	b;

	b = *i;
	a = 0;
	ft_bzero(d, sizeof(d));
	(*i)++;
	while (s && s[*i] && (s[*i] == '_' || ft_isalnum(s[*i])))
		d[a++] = s[(*i)++];
	if (s[(*i)] == '?')
	{
		d[a++] = '?';
		(*i)++;
	}
	d[a] = '\0';
	return (1);
}

static int	cleanret(char **cp, char **s)
{
	ft_strdel(s);
	*s = *cp;
	return (*s && (*s)[0] ? 1 : 0);
}

int			onebyone(char **s, t_var *var, int i, int a)
{
	char	*cp;
	char	tmp[LINE_MAX];
	char	c;

	(!(cp = ft_strnew(0))) ? malloc_failed("onebyone") : 0;
	while (*s && (*s)[i])
	{
		if (!g_global->par && (*s)[i] == '~' && (!(c = quoted(*s, i))
		|| c == 34) && !wstruct(var, &cp, &a, "HOME"))
			i++;
		if (!g_global->par && (*s)[i] == 36 && (!i || (!nbcks(*s, i - 1)
		&& (*s)[i + 1] != 40 && (!(c = quoted(*s, i)) || c == 34)))
		&& askpid(*s, &i, &cp, &a) && cpu(tmp, *s, &i)
		&& ((!ft_strcmp(tmp, "?") && wr(g_global->ret, &cp, &a))
		|| wstruct(var, &cp, &a, tmp)))
			!tmp[0] ? i-- : 0;
		if ((*s)[i] && (((*s)[i] != 36 && (*s)[i] != '~')
		|| ((i && (nbcks(*s, i - 1) || quoted(*s, i) == 39))
		|| ((*s)[i + 1] == 40 && (*s)[i] == 36)))
		&& !(cp = substitute(cp, ft_strsub(*s, i, 1))))
			break ;
		(*s)[i] && ((*s)[i] != 36 || ((i && (nbcks(*s, i - 1)
		|| quoted(*s, i) == 39)) || (*s)[i + 1] == 40)) ? i++ : 0;
	}
	return (cleanret(&cp, s));
}
