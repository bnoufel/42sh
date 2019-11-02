/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmath2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:01:00 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:01 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				alldigit(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != 41)
	{
		if (!ft_isdigit(s[i]) && s[i] != '-' && s[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

static int		casemore(char *s, t_var *var, t_par *par)
{
	long long	i;
	int			r;
	char		*t;

	r = 0;
	t = mathcore(ft_strdup(s), var, par);
	i = ft_atoll(t);
	ft_strdel(&t);
	i++;
	ft_strcpy(s, (t = ft_lltoa(i)));
	ft_strdel(&t);
	return (1);
}

static int		caseless(char *s, t_var *var, t_par *par)
{
	long long	i;
	int			r;
	char		*t;

	r = 0;
	t = mathcore(ft_strdup(s), var, par);
	i = ft_atoll(t);
	ft_strdel(&t);
	i--;
	ft_strcpy(s, (t = ft_lltoa(i)));
	ft_strdel(&t);
	return (1);
}

void			helpinvar(char *s, char o, t_var *var, t_par *par)
{
	if (o == '+')
		casemore(s, var, par);
	else
		caseless(s, var, par);
	if (s[0] == '-' && s[1] == '0')
		ft_memmove(s, s + 1, sizeof(s + 1));
}

int				subinmath(char **s, t_par *par, t_var *var)
{
	int		i;

	i = 1;
	while ((*s)[i])
	{
		if ((*s)[i] == '$' && (*s)[i + 1])
		{
			helptosub(s, &i, par, var);
			i = 1;
		}
		else if ((*s)[i] == 96)
		{
			helpquotes(s, &i, par, &var);
			i = 1;
		}
		i++;
	}
	return (1);
}
