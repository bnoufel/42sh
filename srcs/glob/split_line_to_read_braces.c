/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_to_read_braces.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:38:08 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:38:09 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char			*get_before_braces(char *str, char **core)
{
	int				j;
	int				i;
	char			*tmp;

	j = 0;
	i = 0;
	if (!(tmp = ft_strnew(ft_strlen(str) * 2)))
		malloc_failed("get_before_braces");
	while (str[i])
	{
		if (str[i] == '{' && ckbrs(str + i + 1, core)
		&& (!i || !nbcks(str, i - 1)))
			break ;
		tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	if (str[i] != '{' || (i && nbcks(str, i - 1)))
	{
		ft_strdel(&tmp);
		return (NULL);
	}
	return (tmp);
}

static char			*get_middle_braces(char *str)
{
	int				j;
	int				i;
	char			*tmp;

	i = 0;
	j = 0;
	if (!(tmp = ft_strnew(ft_strlen(str) * 2)))
		malloc_failed("get_middle_braces");
	ft_bzero(tmp, sizeof(tmp));
	while (str[j] && ((str[j] != '{' && !ckbrs(str + i + 1, NULL))
	|| (j && nbcks(str, j - 1))))
		j++;
	while (str[++j])
	{
		if (str[j] == '}' && ckbrs2(str, j) && (!j || !nbcks(str, j - 1)))
			break ;
		tmp[i++] = str[j];
	}
	tmp[i] = '\0';
	return (tmp);
}

static char			*get_after_braces(char *str)
{
	int				j;
	int				i;
	char			*tmp;

	i = 0;
	j = 0;
	if (!(tmp = ft_strnew(ft_strlen(str) * 2)))
		malloc_failed("get_after_braces");
	while (str[j])
	{
		if (str[j] == '}' && ckbrs2(str, j) && (!nbcks(str, j - 1)))
			break ;
		j++;
	}
	if (!str[j])
	{
		ft_strdel(&tmp);
		return (NULL);
	}
	while (str[++j])
		tmp[i++] = str[j];
	tmp[i] = '\0';
	return (tmp);
}

bool				split_folder_braces(t_split *split, char *str,
					char ***core)
{
	if (!(*core = (char **)malloc(3 * sizeof(char *))))
		malloc_failed("split_folder_braces");
	(*core)[0] = NULL;
	(*core)[1] = NULL;
	(*core)[2] = 0;
	split->before = NULL;
	split->middle = NULL;
	split->after = NULL;
	if (!(split->before = get_before_braces(str, *core))
	|| (!(split->middle = get_middle_braces(str)))
	|| (!(split->after = get_after_braces(str))))
	{
		ft_free_tab(*core);
		free_struct_folder(split);
		return (false);
	}
	return (true);
}
