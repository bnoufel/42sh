/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:10:05 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:10:06 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlcpy(char *dst, const char *src, int *len)
{
	size_t i;
	size_t k;

	k = 0;
	i = ft_strlen(src);
	while (k < i)
	{
		dst[k] = src[k];
		k++;
	}
	dst[k] = '\0';
	(*len) += (int)k;
	return (dst);
}
