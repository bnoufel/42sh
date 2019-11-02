/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_tokenizer_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:08:58 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:09:00 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		check_do_token(char **line, int end)
{
	int i;

	i = in_key_value(*line + end) + end;
	if ((*line)[i] == ';')
		i++;
	if ((*line) && (*line)[i])
	{
		while ((*line)[i] == ' ' || (*line)[i] == '\t')
			i++;
		if ((*line)[i] && (*line)[i] == 'd')
		{
			if ((*line)[i + 1] && (*line)[i + 1] == 'o')
				return (0);
			ft_putendl_fd("\nmissing 'do' keyword", 2);
			return (-1);
		}
		else if ((*line)[i])
		{
			ft_putendl_fd("\nmissing 'do' keyword", 2);
			return (-1);
		}
	}
	return (0);
}

int		check_for_token_2(char **line, int *end, int test, t_par *par)
{
	int i;
	int len;

	i = 0;
	if (check_do_token(line, *end) == -1)
		return (-1);
	if ((i = find_key_pos(line, "do", *end + test, par)) == -1)
	{
		len = ft_strlen(*line) - 1;
		if (g_global->sub || g_global->sig || g_global->stdi)
			return (-1);
		else if (g_global->f_fd > 0)
		{
			if ((str_to_gnl(line, g_global->f_fd)) == -1)
				return (-1);
		}
		else
			ft_mini_read(line, &len, 1, ';');
		if ((i = find_key_pos(line, "do", *end + test, par) == -1))
		{
			g_global->sig ? 0 : ft_putendl_fd("\nmissing 'do' keyword", 2);
			return (-1);
		}
	}
	return (i);
}

int		in_key_value(char *line)
{
	int		i;
	int		is_value;

	i = 0;
	is_value = 0;
	while (line[i] && line[i] != ';')
	{
		if (ft_strequ(line + i, " in "))
		{
			if ((i + 4) <= (int)ft_strlen(line))
				i += 4;
			while (line[i] && line[i] != ';')
			{
				if (line[i] != ' ' && line[i] != '\t')
					is_value = 1;
				i++;
			}
			if ((!line[i] || line[i] == ';') && is_value == 1)
				return (i);
			return (0);
		}
		i++;
	}
	return (0);
}
