/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_folder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:03:46 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:09:27 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char	*ac_open_folder2(const char *s, int c)
{
	int		len;
	int		i;
	char	*str;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	while (s[len] != c)
		len--;
	if (len == 0 && s[len] == '/')
	{
		if (!(str = ft_strdup("/")))
			malloc_failed("ac_open_folder");
		return (str);
	}
	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		malloc_failed("ac_open_folder");
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char		*ac_open_folder(const char *s, int c)
{
	char	*str;
	DIR		*odir;

	if (!ft_strchr(s, c))
		return (NULL);
	if ((odir = opendir(s)))
	{
		if (!(str = ft_strdup(s)))
			malloc_failed("ac_open_folder");
		closedir(odir);
		return (str);
	}
	return (ac_open_folder2(s, c));
}
