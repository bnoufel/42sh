/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpenv2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:33:12 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:33:14 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		env_strequ(char const *s1, char const *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s1[i] != '=' && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (!s2[i] && s1[i] == '=')
		return (1);
	return (0);
}

int		ckvar(char *t)
{
	if (t && ft_strchr(t, '='))
		*(ft_strchr(t, '=')) = '\0';
	else
	{
		ft_strdel(&t);
		return (0);
	}
	if (*t == '=' || *t == '(' || *t == '.' || *t == '/' || checkvarname(t))
	{
		ft_strdel(&t);
		return (0);
	}
	ft_strdel(&t);
	return (1);
}

void	noshlvlcase(t_env **tmp, t_env **head, int a)
{
	t_env *env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		malloc_failed("copyenv");
	ft_bzero(env->elem, sizeof(env->elem));
	env->next = NULL;
	!a ? *head = env : 0;
	*tmp ? (*tmp)->next = env : 0;
	ft_strcpy(env->elem, "SHLVL=1");
	*tmp = env;
	env = env->next;
}

char	*cksubmath(char **s, t_var *var, t_par *par, int *l)
{
	int		i;
	char	c;

	i = -1;
	c = 0;
	*l = *l == 2 ? 1 : 0;
	while (*s && (*s)[++i])
	{
		if (i && (*s)[i] == 40 && (*s)[i - 1] == '$' && (!(i - 1)
		|| (!nbcks(*s, i - 2) && (!(c = quoted(*s, i - 1)) || c == 34))))
		{
			*l = 1;
			c == 34 ? (par->q = 1) : 0;
			helpbrackets(s, &i, &par, &var);
			return (*s);
		}
		else if ((*s)[i] == 96 && (!(c = quoted(*s, i)) || c == 34)
		&& (!i || (!nbcks(*s, i - 1))) && (*l = 2))
		{
			c == 34 ? (par->q = 1) : 0;
			helpquotes(s, &i, par, &var);
			return (cksubmath(s, var, par, l));
		}
	}
	return (*s);
}

char	quoted(char *s, int i)
{
	char	c;
	int		n;

	c = 0;
	n = 0;
	while (--i >= 0)
	{
		if (s[i] == 34 && (!c || c == 34))
		{
			c = 34;
			n++;
		}
		else if (s[i] == 39 && (!c || c == 39))
		{
			c = 39;
			n++;
		}
	}
	return (n % 2 ? c : 0);
}
