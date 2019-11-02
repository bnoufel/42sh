/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lltoa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 11:51:45 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 16:10:47 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sizen(long long n)
{
	long long	nb;
	int			count;

	nb = n;
	count = 0;
	if (nb < 0)
	{
		count++;
		nb = -nb;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		count++;
	}
	count++;
	return (count);
}

char		*lltoa(long long n)
{
	char		*s;
	int			i;
	long long	nb;

	i = sizen(n) - 1;
	nb = n;
	if (!(s = (char *)malloc((i + 2) * sizeof(char))))
		return (0);
	if (nb < 0)
		nb = -nb;
	while (nb > 9)
	{
		s[i] = (nb % 10) + '0';
		nb = nb / 10;
		i--;
	}
	s[i] = nb + 48;
	if (n < 0)
	{
		i--;
		s[i] = '-';
	}
	s[sizen(n)] = '\0';
	return (s);
}
