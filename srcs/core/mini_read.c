/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:59:32 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:12 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				left_right(t_list **list, char *buff, int *i)
{
	if (buff[2] == 'C')
	{
		if ((*list)->next->next)
		{
			*list = (*list)->next;
			(*list)->state = 0;
			(*list)->next->state = 1;
			(*i)++;
		}
		return (1);
	}
	else if (buff[2] == 'D')
	{
		if ((*list)->prev)
		{
			if ((*list) && (*list)->erase == 1)
				return (1);
			(*list)->next->state = 0;
			*list = (*list)->prev;
			(*list)->next->state = 1;
			(*i)--;
		}
		return (1);
	}
	return (0);
}

void			ft_add_realloc(char **cmd, char c, int pos)
{
	char		*str;
	int			i;
	int			j;
	int			size;

	size = (int)ft_strlen(*cmd);
	j = 0;
	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * (size + 1 + 1))))
		return ;
	while (i < size)
	{
		if (i == pos)
			str[i + j++] = c;
		str[i + j] = (*cmd)[i];
		i++;
	}
	str[i + j] = '\0';
	free(*cmd);
	*cmd = str;
}

static char		*ft_help_mini_read(int *pos, char **cmd, int qdbs, char c)
{
	char		*buff;

	if (!(buff = (char*)malloc(sizeof(char) * 9)))
		malloc_failed("loop");
	ft_bzero(buff, 8);
	*pos = (int)ft_strlen(*cmd) - 2;
	ft_qdbs((*g_global->cursor), g_global->list, g_global->first, qdbs);
	init_term((*g_global->cursor), 0, g_global->var, 0);
	(*g_global->cursor)->col += 1;
	count_and_erase_line((*g_global->cursor), g_global->first, 3);
	ft_info_line(*g_global->cursor, g_global->var);
	ft_read_list(g_global->first, (*g_global->cursor), 1);
	if (*pos == -1 || (*cmd)[*pos] != ';')
		ft_add_realloc(cmd, c, ++(*pos));
	return (buff);
}

static void		ft_change_sig(void)
{
	if (g_global->sig == 3)
	{
		count_and_erase_line((*g_global->cursor), g_global->first, 3);
		g_global->sig = 2;
	}
}

int				ft_mini_read(char **cmd, int *i, int qdbs, char c)
{
	int			pos;
	char		*buff;

	buff = ft_help_mini_read(&pos, cmd, qdbs, c);
	if (ft_mini_loop(i, &pos, cmd, buff) == 0)
	{
		while ((*g_global->cursor)->history->next)
			(*g_global->cursor)->history = (*g_global->cursor)->history->next;
		init_cursor(*g_global->cursor, 0);
		if (qdbs == 4)
		{
			ft_change_sig();
			return (0);
		}
		if (g_global->sig == 3)
		{
			ft_putendl_fd("\nmysh : syntax error: unexpected end of file\n", 2);
			g_global->sig = 1;
		}
		return (0);
	}
	if (tcsetattr(0, TCSANOW, (*g_global->cursor)->old) == -1)
		ft_bye_bye(g_global->var, 0, NULL, 1);
	return (1);
}
