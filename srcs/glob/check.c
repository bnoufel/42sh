/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:37:30 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:37:32 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

bool				number_braces_valid(char *str)
{
	int	i;

	i = str[0] == '-' ? 1 : 0;
	while (str[i])
	{
		if (str[i] <= '9' && str[i] >= '0')
			i++;
		else
			return (false);
	}
	return (true);
}

static int			ckbrs12(char *s, char **core, int c, int i)
{
	int a;

	if (!c && s[i] != '\\' && s[i] >= 32 && s[i] <= 126)
		i++;
	core && !core[0] ? core[0] = ft_strsub(s, 0, i) : 0;
	if (s[i] == '.' && s[i + 1] == '.')
		i += 2;
	else
		return (0);
	if (s[i] == '\\')
		i++;
	a = i;
	if (s[i] != '\\' && s[i] >= 32 && s[i] <= 126)
		i++;
	while (c && (s[i] == '\\' || (s[i] <= '9' && s[i] >= '0')))
	{
		if (s[i] == '\\' && !nbcks(s, i))
			return (0);
		i++;
	}
	core && !core[1] ? core[1] = ft_strsub(s, a, i - a) : 0;
	core ? core[2] = 0 : 0;
	return (s[i] != '}' ? 0 : 1);
}

int					ckbrs(char *s, char **core)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (s[i] == '\\')
		i++;
	if (s[i] == '-' && (!i || nbcks(s, i - 1)))
	{
		i++;
		c = 1;
	}
	while (s[i] == '\\' || (s[i] <= '9' && s[i] >= '0'))
	{
		if (i && s[i] == '\\' && !nbcks(s, i))
			return (0);
		else if (s[i] <= '9' && s[i] >= '0')
			c = 1;
		i++;
	}
	return (ckbrs12(s, core, c, i));
}

static int			ckbrs22(char *s, int j)
{
	int	i;

	i = j;
	while (j && (s[j] == '\\' || (s[j] <= '9' && s[j] >= '0')
	|| (s[j] == '-' && s[j - 1] == '{')))
	{
		if (s[j] == '\\' && !nbcks(s, j))
			return (0);
		j--;
	}
	if (i == j && s[j] != '\\' && s[j] >= 32 && s[j] <= 126)
		j--;
	if (s[j] == '\\')
		j--;
	return (s[j] != '{' ? 0 : 1);
}

int					ckbrs2(char *s, int j)
{
	int	i;

	if (!j)
		return (0);
	j--;
	i = j;
	while (j && (s[j] == '\\' || (s[j] <= '9' && s[j] >= '0')
	|| (s[j] == '-' && s[j - 1] == '.')))
	{
		if (s[j] == '\\' && !nbcks(s, j))
			return (0);
		j--;
	}
	if (i == j && j && s[j] != '\\' && s[j] >= 32 && s[j] <= 126)
		j--;
	if (s[j] == '\\')
		j--;
	if (j && s[j] == '.' && s[j - 1] == '.')
		j -= 2;
	else
		return (0);
	return (ckbrs22(s, j));
}
