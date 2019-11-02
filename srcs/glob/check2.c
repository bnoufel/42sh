/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:37:36 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:37:38 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

bool			check_max(long min, long max, long *diff)
{
	if (min < max)
	{
		*diff = max - min;
		if (max - min >= INT_MAX || max - min < INT_MIN)
		{
			ft_putstr("mysh: too long: ");
			ft_putendl(g_global->cmdline);
			return (false);
		}
	}
	else
	{
		*diff = min - max;
		if (min - max >= INT_MAX || min - max < INT_MIN)
		{
			ft_putstr("mysh: too long: ");
			ft_putendl(g_global->cmdline);
			return (false);
		}
	}
	return (true);
}

bool			check_is_valid_number(char *min, char *max)
{
	int			i;

	i = (min[0] == '-' || min[0] == '+') ? 1 : 0;
	while (min[i])
	{
		if (min[i] < '0' || min[i] > '9')
			return (false);
		i++;
	}
	i = (max[0] == '-' || max[0] == '+') ? 1 : 0;
	while (max[i])
	{
		if (max[i] < '0' || max[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static int		ckhks2(char *s, int i, int ec[3])
{
	if (s[i] == '-')
		return (0);
	while (s[i] && (s[i] != ']' || nbcks(s, i - 1)))
		i++;
	if (s[i] != ']')
	{
		ec[0] = 0;
		ec[1] = 0;
		return (0);
	}
	return (1);
}

int				ckhks(char *s, int i, int ec[3])
{
	ec[0] = 0;
	ec[1] = 0;
	ec[2] = 0;
	i++;
	while (s[i] && (s[i] != ']' || nbcks(s, i - 1))
			&& (s[i] != '-' || nbcks(s, i - 1)))
		i++;
	if (s[i] == '-')
	{
		s[i + 1] == '-' ? i++ : 0;
		ec[0] = s[i - 1] != '-' || (s[i - 2] == '[' && (!(i - 2)
					|| !nbcks(s, i - 3))) ? s[i - 1] : 0;
		i++;
		while (s[i] == '\\')
			i++;
		ec[1] = s[i] && s[i] != '-' && (s[i] != ']' || (i && nbcks(s, i - 1)))
			? s[i] : 0;
	}
	return (ckhks2(s, i, ec));
}
