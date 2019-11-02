/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupspec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:37:44 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:37:45 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char		*dupspec(char *s1)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(dest = (char *)malloc(sizeof(char) * 2 * (ft_strlen(s1) + 1))))
		return (NULL);
	if (!s1)
		return (dest);
	while (s1[i])
	{
		if (((s1[i] == '`' || s1[i] == '$' || s1[i] == '?' || s1[i] == '*'
		|| s1[i] == ' ' || s1[i] == '{' || s1[i] == '}'
		|| s1[i] == '[' || s1[i] == ']') && (!i || !nbcks(s1, i - 1)))
		|| (s1[i] == '\\' && nbcks(s1, i)))
			dest[j++] = '\\';
		dest[j++] = s1[i++];
	}
	dest[j] = '\0';
	return (dest);
}
