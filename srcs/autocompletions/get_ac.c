/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ac.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:06:19 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:06:22 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int		ac_count_space(char *str)
{
	int			i;
	int			len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == 32)
			len++;
		i++;
	}
	return (len);
}

char			*ac_add_backslash(char *str)
{
	int			i;
	int			j;
	char		*tmp;

	i = 0;
	j = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(str)
		+ ac_count_space(str) + 2))))
		malloc_failed("ac_add_backslash");
	while (str[i])
	{
		if (str[i] == 32)
		{
			tmp[j] = '\\';
			j++;
		}
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char			*ac_remove_backslash(char *str)
{
	int			i;

	i = 0;
	while (str[i] && str[i] != '\\')
		i++;
	if (i == (int)ft_strlen(str))
		return (str);
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	return (str);
}

void			*ac_get_occu(t_split *folder, int bin, t_var **var)
{
	t_auto		*lst;
	char		*pwd;
	char		*old;

	(!(old = ft_strdup(folder->middle))) ? malloc_failed("ac_get_occu") : 0;
	if (bin == 1)
	{
		if (folder->middle[0] == '\0' || !(ft_strchr(folder->middle, '/')))
			lst = ac_readdir_bin(ft_getenv("PATH", var), folder, -1, bin);
		else
			lst = ac_readdir_bin(NULL, folder, -1, bin);
		free(old);
	}
	else
	{
		if (folder->middle[0] != '/')
		{
			if (!(pwd = ft_strjoinfree(getcwd(NULL, PATH_MAX), "/", 1)))
				malloc_failed("ac_get_occu");
			if (!(folder->middle = ft_strjoinfree(pwd, folder->middle, 3)))
				malloc_failed("ac_get_occu");
		}
		lst = ac_read_path_bin(folder, bin, old);
	}
	return (lst);
}
