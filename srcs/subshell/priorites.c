/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorites.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:01:13 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:14 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		fope(char *s)
{
	if (ft_strlen(s) >= 2 && ft_strequ(s, "**"))
		return (2);
	return (0);
}

int		sope(char *s)
{
	if ((*s == '%' || *s == '*' || *s == '/') && s[1] != '=')
		return (1);
	return (0);
}

int		tope(char *s)
{
	if (s[0] == '+' && ckop(s) && (s[1] != '+' || (s[2] && s[2] == '+'))
	&& ((s[-1] && s[-1] != '+') || (s[-1] && s[-2] && s[-2] == '+'))
	&& s[1] != '=')
		return (1);
	else if (s[0] == '-' && ckop(s) && (s[1] != '-' || (s[2] && s[2] == '-'))
	&& ((s[-1] && s[-1] != '-') || (s[-1] && s[-2] && s[-2] == '-'))
	&& s[1] != '=')
		return (1);
	return (0);
}

int		fthope(char *s)
{
	if (ft_strlen(s) >= 2 && (ft_strequ(s, "!=") || ft_strequ(s, "<=")
	|| ft_strequ(s, ">=") || ft_strequ(s, "==")))
		return (2);
	else if ((*s == '>' && s[1] != '>') || (*s == '<' && s[1] != '<'))
		return (1);
	return (0);
}

int		sthope(char *s)
{
	if (ft_strlen(s) >= 2 && (ft_strequ(s, "&&") || ft_strequ(s, "||")))
		return (2);
	return (0);
}
