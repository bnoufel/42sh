/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msc_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:09:12 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:09:13 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char	*secured_malloc(char *str, int start, int end, char *error)
{
	char *new_str;

	if (start != -1 && end != -1)
	{
		if (start < 0 || end < 0)
			malloc_failed(error);
		if (!(new_str = ft_strsub(str, start, end)))
			malloc_failed(error);
		return (new_str);
	}
	else
	{
		if (!(new_str = ft_strdup(str)))
			malloc_failed(error);
		return (new_str);
	}
}

int		special_strlen(char *line)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] != ';' && line[i] != ' ' && line[i] != '\t')
			k++;
		i++;
	}
	if (k == 0)
		return (0);
	return (1);
}
