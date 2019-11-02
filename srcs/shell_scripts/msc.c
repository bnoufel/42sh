/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:09:10 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:09:11 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		read_script(char **line)
{
	int len;

	len = ft_strlen(*line) - 1;
	if (g_global->sub || g_global->sig)
		return (-1);
	if (g_global->f_fd > 0 || g_global->stdi)
	{
		if ((str_to_gnl(line, g_global->f_fd)) == -1)
			return (-1);
	}
	else
	{
		ft_mini_read(line, &len, 1, ';');
		ft_cursorless();
	}
	return (0);
}

void	free_if_list(t_if_list **list, int flag)
{
	t_if_list	*to_free;
	t_if_list	*tmp;

	to_free = *list;
	while (to_free && flag == 1)
	{
		ft_strdel(&to_free->if_cond);
		tmp = to_free;
		to_free = to_free->next;
		free(tmp);
		tmp = NULL;
	}
	if (flag == 0)
	{
		ft_strdel(&(*list)->then);
		free(*list);
		*list = NULL;
		list = NULL;
	}
}

int		is_key(char *line, char *key, int flag, int pos)
{
	int	i;
	int	saved_pos;

	saved_pos = pos;
	i = 0;
	if (pos && line[pos - 1] != ' ' && line[pos - 1] != ';'
			&& line[pos - 1] != '\t')
		return (0);
	while (key[i] && line[pos] && line[pos++] == key[i])
		i++;
	if (key[i] || (line[pos] && line[pos] != ' ' && line[pos] != ';'
				&& line[pos] != '\t'))
		return (0);
	else if (flag == 2)
	{
		while (line[pos])
		{
			if (ft_strequ(line + pos, " in ")
					&& in_key_value(line + saved_pos) > 0)
				return (1);
			pos++;
		}
		return (0);
	}
	return (1);
}

int		check_script_tokenizer(char **line, int *end, int ground, t_par *par)
{
	if (is_key(*line, "fi", 0, *end) == 1 || is_key(*line, "else", 1, *end) == 1
		|| is_key(*line, "elif", 1, *end) == 1
		|| is_key(*line, "do", 0, *end) == 1
		|| is_key(*line, "done", 0, *end) == 1)
	{
		ft_putstr_fd("\nForbbiden keyword found\n", 2);
		return (-1);
	}
	if (is_key(*line, "while", 1, *end) == 1)
		return (check_while_token(line, ground, end, par));
	if (is_key(*line, "if", 3, *end) == 1)
		return (check_if(line, ground, end, par));
	if (is_key(*line, "for", 2, *end) == 1)
		return (check_for_token(line, ground, end, par));
	return (1);
}

int		skip_comment(char **line)
{
	int		i;
	char	*tmp;
	char	*str;

	i = 0;
	tmp = *line;
	while (tmp[i])
	{
		if (tmp[i] == '#' && i > 0)
		{
			str = ft_strsub(tmp, 0, i);
			str = ft_strjoinfree(str, " ", 1);
			ft_strdel(line);
			*line = str;
			return (1);
		}
		else if (tmp[i] == '#')
		{
			ft_strdel(line);
			return (2);
		}
		i++;
	}
	return (0);
}
