/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmain3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:58:31 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:09 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		ft_ioctl(t_cursor *cursor)
{
	struct winsize	window;

	ft_putstr_fd("\x1b[?25l", 0);
	ioctl(0, TIOCGWINSZ, &window);
	cursor->window = window;
}

char		*ft_putstr_special(char *str, char c)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		malloc_failed("putstr special");
	while (str[i] && str[i] != c)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void		ft_choose_prompt(t_cursor *cursor, t_var *var, t_list *first)
{
	if (g_global->bg == 0)
	{
		if (g_global->sig != 1)
			ft_info_line(cursor, &var);
		ft_read_list(first, cursor, 1);
	}
	else if (g_global->bg == 1)
	{
		ft_read_list(first, cursor, 4);
		g_global->bg = 2;
	}
	else
		ft_read_list(first, cursor, 3);
}
