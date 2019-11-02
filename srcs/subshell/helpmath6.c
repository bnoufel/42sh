/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmath6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:01:06 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:08 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		calcul(char *ope, long long l[3])
{
	if (ft_strlen(ope) >= 2 && ft_strequ(ope, "**"))
		l[0] = ft_iterative_power(l[1], l[2]);
	else if (ft_strlen(ope) >= 2 && ft_strequ(ope, "<<") && ope[2] != '=')
		l[0] = l[1] << l[2];
	else if (ft_strlen(ope) >= 2 && ft_strequ(ope, ">>") && ope[2] != '=')
		l[0] = l[1] >> l[2];
	else if (*ope == '^' && ope[1] != '=')
		l[0] = l[1] ^ l[2];
	else if (*ope == '|' && ope[1] != '|' && ope[1] != '=')
		l[0] = l[1] | l[2];
	else if (*ope == '&' && ope[1] != '&' && ope[1] != '=')
		l[0] = l[1] & l[2];
	else if (*ope == '*' && ope[1] != '=')
		l[0] = l[1] * l[2];
	return (calcul2(ope, l));
}

int		comparaison(char *ope, long long l[3])
{
	if (ft_strlen(ope) >= 2 && ft_strequ(ope, "!="))
		l[0] = (l[1] != l[2]) ? 1 : 0;
	else if (ft_strlen(ope) >= 2 && ft_strequ(ope, "<="))
		l[0] = (l[1] <= l[2]) ? 1 : 0;
	else if (ft_strlen(ope) >= 2 && ft_strequ(ope, ">="))
		l[0] = (l[1] >= l[2]) ? 1 : 0;
	else if (ft_strlen(ope) >= 2 && ft_strequ(ope, "=="))
		l[0] = (l[1] == l[2]) ? 1 : 0;
	else if (*ope == '<' && ope[1] != '<')
		l[0] = (l[1] < l[2]) ? 1 : 0;
	else if (*ope == '>' && ope[1] != '>')
		l[0] = (l[1] > l[2]) ? 1 : 0;
	else if (ft_strlen(ope) >= 2 && ft_strequ(ope, "&&"))
		l[0] = (l[1] && l[2]) ? 1 : 0;
	else if (ft_strlen(ope) >= 2 && ft_strequ(ope, "||"))
		l[0] = (l[1] || l[2]) ? 1 : 0;
	return (1);
}

int		assigntovar(int r, char *v, t_var *var)
{
	char tr[LINE_MAX];
	char *myr;

	trncat(tr, v);
	if (!ft_isalpha(tr[0]))
		return (0);
	myr = lltoa(r);
	ft_strcat(ft_strcat(tr, "="), myr);
	helpchkivar(0, 0, &var, tr);
	ft_strdel(&myr);
	return (1);
}

void	helpmact2(t_var *var, char tr[LINE_MAX], t_par *par, long long *r)
{
	int		t;
	char	*te;

	t = 0;
	if (var && ((te = retenv(var->lenv, tr))
	|| (te = retenv(var->loc, tr))))
	{
		te = mathcore(ft_strdup(te), var, par);
		*r = ft_atoll(te);
		ft_strdel(&te);
	}
}
