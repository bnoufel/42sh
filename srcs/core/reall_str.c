/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reall_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:59:47 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:15 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			ft_delete_realloc(char **cmd, int pos)
{
	char			*str;
	int				i;
	int				j;
	int				size;

	size = (int)ft_strlen(*cmd);
	i = 0;
	j = 0;
	if (!(str = (char*)malloc(sizeof(char) * size)))
		return ;
	while (i < size)
	{
		if (i == pos - 1)
			j++;
		str[i] = (*cmd)[i + j];
		i++;
	}
	free(*cmd);
	*cmd = str;
}

void			ft_delete_mini(int *i, int *pos, char **cmd)
{
	if ((*g_global->list) && (*g_global->list)->erase != 1)
	{
		(*i)--;
		ft_delete_realloc(cmd, (*pos) + 1);
		(*pos)--;
	}
	ft_free_left_node(g_global->list);
}

int				ft_mini_want(char *buff, int *i, int *pos, char **cmd)
{
	if (buff[0] == 4 && buff[1] == 0)
	{
		if (((*cmd)[*pos] == '\n' && (*cmd)[(*pos) + 2])
		|| (((*cmd)[*pos] != '\n' && (*cmd)[*pos] != ';')
		&& (*cmd)[*pos] != ' ' && (*cmd)[(*pos) + 1]))
		{
			if ((*g_global->list)->next->next)
			{
				(*i)--;
				ft_delete_realloc(cmd, (*pos) + 2);
				ft_free_right_node(g_global->list);
			}
			return (1);
		}
		g_global->sig = 3;
		return (1);
	}
	else if ((buff[0] == '\n') || (left_right(g_global->list, buff, pos) != 0))
		;
	else if (buff[0] == 0x7f && buff[1] == '\0')
		ft_delete_mini(i, pos, cmd);
	else if ((buff[0] >= 32 && buff[0] <= 126) && buff[1] == '\0')
		return (0);
	return (1);
}
