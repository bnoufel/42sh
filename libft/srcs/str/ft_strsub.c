/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:10:38 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:10:40 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	str = NULL;
	if (!(str = (char *)(malloc(sizeof(char) * (len + 1)))))
		return (NULL);
	if (!s)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i + start] != '\t' ? s[i + start] : ' ';
		i++;
	}
	str[i] = '\0';
	return (str);
}
