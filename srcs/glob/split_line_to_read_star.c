/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_to_read_star.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:38:20 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:38:22 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char			*get_before_star(char *str)
{
	int				i;
	int				j;
	char			*tmp;

	i = 0;
	j = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		malloc_failed("get_before_star");
	while (str[j])
	{
		if ((str[j] == '*' || str[j] == '?') && (!j || !nbcks(str, j - 1)))
			break ;
		j++;
	}
	while (j >= 0 && str[j] && str[j] != '/')
		j--;
	while (i <= j)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

static char			*get_middle_star(char *str)
{
	int				i;
	int				j;
	char			*tmp;

	i = 0;
	j = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		malloc_failed("get_before_star");
	while (str[j])
	{
		if ((str[j] == '*' || str[j] == '?') && (!j || !nbcks(str, j - 1)))
			break ;
		j++;
	}
	while (j >= 0 && str[j] && str[j] != '/')
		j--;
	j++;
	while (str[j] && str[j] != '/')
		tmp[i++] = str[j++];
	tmp[i] = '\0';
	return (tmp);
}

static char			*get_after_star(char *str)
{
	int				i;
	int				j;
	char			*tmp;

	i = 0;
	j = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		malloc_failed("get_before_star");
	while (str[j])
	{
		if ((str[j] == '*' || str[j] == '?') && (!j || !nbcks(str, j - 1)))
			break ;
		j++;
	}
	while (str[j] && str[j] != '/')
		j++;
	while (str[j])
	{
		tmp[i] = str[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}

bool				split_folder_star(t_split *split, char *str)
{
	if (!(split->before = get_before_star(str)))
		return (false);
	if (!(split->middle = get_middle_star(str)))
		return (false);
	if (!(split->after = get_after_star(str)))
		return (false);
	return (true);
}
