/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:58:03 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:07 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	cut(char c, char **str, char **line, int cut)
{
	char		*tmp;

	if (!(*line = ft_strsub(*str, 0, ft_strlen(*str)
					- ft_strlen(ft_strchr(*str, c)))))
		malloc_failed("cut1");
	tmp = *str;
	if (!(*str = ft_strsub(*str, (int)ft_strlen(*line) + 1,
	ft_strlen(*str) - ft_strlen(*line))))
		malloc_failed("cut2");
	if (cut && (*line)[0] != '\0')
	{
		if (!(*line = ft_strjoinfree(*line, " ", 1)))
			malloc_failed("gnl");
	}
	ft_strdel(&tmp);
}

int		del(char **str, int ret)
{
	ft_strdel(str);
	return (ret);
}

int		gnl(int fd, char **line, int c)
{
	int			ret;
	char		buff[1001];
	static char	*str = NULL;

	ret = 0;
	if (fd < 0 || !line)
		return (del(&str, -1));
	while (!ft_strchr(str, '\n') && ((ret = read(fd, buff, 1000)) > 0))
	{
		buff[ret] = '\0';
		if (!(str = ft_strjoinfree(str, buff, 1)))
			malloc_failed("gnl");
	}
	if (ret == -1)
		return (del(&str, -1));
	if (ft_strchr(str, '\n'))
		cut('\n', &str, line, c);
	else
	{
		if (ft_strlen(str) > 0 && ft_strchr(str, '\0'))
			cut('\0', &str, line, c);
		else
			return (del(&str, 0));
	}
	return (1);
}
