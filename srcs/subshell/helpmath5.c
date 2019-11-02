/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmath5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:01:05 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:05 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			assignation(char *ope, long long l[3], char *v, t_var *var)
{
	if (ft_strlen(ope) >= 3 && ft_strequ(ope, "<<="))
		l[0] = l[1] << l[2];
	else if (ft_strlen(ope) >= 3 && ft_strequ(ope, ">>="))
		l[0] = l[1] >> l[2];
	else if (ft_strlen(ope) >= 2 && ft_strequ(ope, "&="))
		l[0] = l[1] & l[2];
	else if (ft_strlen(ope) >= 2 && ft_strequ(ope, "*="))
		l[0] = l[1] * l[2];
	else if (ft_strlen(ope) >= 2 && ft_strequ(ope, "+="))
		l[0] = l[1] + l[2];
	else if (ft_strlen(ope) >= 2 && ft_strequ(ope, "-="))
		l[0] = l[1] - l[2];
	else if (ft_strlen(ope) >= 2 && ft_strequ(ope, "^="))
		l[0] = l[1] ^ l[2];
	else if (ft_strlen(ope) >= 2 && ft_strequ(ope, "/="))
		l[0] = l[1] / l[2];
	else if (ft_strlen(ope) >= 2 && ft_strequ(ope, "%="))
		l[0] = l[1] % l[2];
	else if (*ope == '=' && ope[1] != '=')
		l[0] = l[2];
	else
		return (calcul(ope, l));
	return (assigntovar(l[0], v, var));
}

long long	mact(char *s, int i, t_var *var, t_par *par)
{
	long long	r;
	int			t[3];
	char		*v;
	char		*v2;
	char		tr[LINE_MAX];

	ft_bzero(tr, sizeof(tr));
	r = 0;
	v = par->br ? afterop(s + i) : beforeop(s, i - isope(s) - 1);
	v2 = trncat(tr, v);
	if (alldigit(v2) || (!par->br && !v2[0]))
		return (ft_atoll(tr));
	else if (!v2[0] && par->br)
		return (0);
	else
	{
		helpmact(v, tr, t);
		(((v[0] == '+' && v[1] == '+') || (v[0] == '-' && v[1] == '-'))
		&& v[0] != t[1]) ? incremvar(tr, var, v[0], par) : 0;
		helpmact2(var, tr, par, &r);
		(t[1] == '+' || t[1] == '-') ? incremvar(tr, var, (char)t[1], par) : 0;
	}
	return (t[0] ? (r *= -1) : r);
}

void		helpmact(char *v, char tr[LINE_MAX], int t[3])
{
	t[0] = 0;
	t[2] = 0;
	if (tr[0] == '-')
	{
		t[0] = 1;
		ft_strcpy(tr, tr + 1);
	}
	t[1] = v[ft_strlen(tr)];
	t[1] = (v[ft_strlen(tr)] && t[1] == v[ft_strlen(tr) + 1])
	? v[ft_strlen(tr) + 1] : 0;
}

int			wop(int op, int (**ope)(char *))
{
	if (op == 1)
		*ope = &bwise;
	else if (op == 2)
		*ope = &fope;
	else if (op == 3)
		*ope = &sope;
	else if (op == 4)
		*ope = &tope;
	else if (op == 5)
		*ope = &fthope;
	else if (op == 6)
		*ope = &sthope;
	else if (op == 7)
		*ope = &lope;
	return (op < 8 ? 1 : 0);
}
