/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:10:02 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:10:03 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strjoinfree(char *s1, char *s2, size_t tofree)
{
	char	*new_str;

	if (!(new_str = s1 ? ft_strjoin(s1, s2) : ft_strdup(s2)))
		return (NULL);
	if (tofree == 1)
		ft_strdel(&s1);
	else if (tofree == 2)
		ft_strdel(&s2);
	else if (tofree == 3)
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
	return (new_str);
}
