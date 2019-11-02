/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitutions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:09:16 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:09:16 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	sub_x(char **line, int i, int x)
{
	char	*first_tmp;
	char	*tmp;
	size_t	len;

	len = ft_strlen(*line + i + 1);
	tmp = ft_strsub(*line + i + 1, 0, len);
	first_tmp = ft_strsub(*line, 0, i - 1);
	if (g_global->o_ac > x + 1)
		first_tmp = ft_strjoinfree(first_tmp, g_global->o_av[x + 1], 1);
	first_tmp = ft_strjoinfree(first_tmp, tmp, 3);
	ft_strdel(line);
	*line = first_tmp;
	return (substitution(line));
}

static int	sub_at(char **line, int i)
{
	char	*first_tmp;
	char	*tmp;
	char	*tab_to_char;
	size_t	len;

	len = ft_strlen(*line + i);
	tmp = ft_strsub(*line + i, 0, len);
	first_tmp = ft_strsub(*line, 0, i - 2);
	if (g_global->o_ac > 2)
	{
		tab_to_char = transform_tab_to_char(g_global->o_av + 2);
		first_tmp = ft_strjoinfree(first_tmp, tab_to_char, 3);
	}
	first_tmp = ft_strjoinfree(first_tmp, tmp, 3);
	ft_strdel(line);
	*line = first_tmp;
	return (substitution(line));
}

int			substitution(char **line)
{
	char	x_len[11];
	int		i;

	i = 0;
	if ((i = find_key_pos(line, "$@", 0, NULL)) != -1)
		sub_at(line, i);
	if ((i = find_key_pos(line, "$", 0, NULL)) != -1
	&& ft_isdigit((*line)[i]))
	{
		x_len[0] = (*line)[i];
		x_len[1] = '\0';
		sub_x(line, i, ft_atoi(x_len));
		ft_bzero(x_len, sizeof(x_len));
	}
	return (0);
}
