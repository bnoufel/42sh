/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_to_read_hook.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:38:13 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/19 11:09:45 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char			*get_before(char *str, int ec[3])
{
	int				j;
	int				i;
	char			*tmp;

	j = 0;
	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen(str) * 2)))
		malloc_failed("get_before");
	while (str[i])
	{
		if (str[i] == '[' && ckhks(str, i, ec) && (!i || !nbcks(str, i - 1)))
			break ;
		tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	if (str[i] != '[' || (i && nbcks(str, i - 1)))
	{
		ft_strdel(&tmp);
		return (NULL);
	}
	return (tmp);
}

static char			*get_middle(char *str)
{
	int				j;
	int				i;
	char			*tmp;

	i = 0;
	j = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		malloc_failed("get_before_hook");
	ft_bzero(tmp, ft_strlen(str));
	while (str[j] != '[' || (j && nbcks(str, j - 1)))
		j++;
	while (str[++j])
	{
		if (str[j] == ']' && !nbcks(str, j - 1))
			break ;
		tmp[i++] = str[j];
	}
	if (str[j] != ']' || nbcks(str, j - 1))
		return (NULL);
	tmp[i] = '\0';
	return (tmp);
}

static char			*get_after(char *str)
{
	int				j;
	int				i;
	char			*tmp;

	i = 0;
	j = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * 2 * ft_strlen(str))))
		malloc_failed("get_before_hook");
	while (str[j] && str[j] != '[')
		j++;
	while (str[j] && (str[j] != ']' || (j && nbcks(str, j - 1))))
		j++;
	while (str[++j])
		tmp[i++] = str[j];
	tmp[i] = '\0';
	return (tmp);
}

bool				split_folder_hook(t_split *split, char *str,
					int ec[3])
{
	split->before = NULL;
	split->middle = NULL;
	split->after = NULL;
	if (!(split->before = get_before(str, ec))
	|| !(split->middle = get_middle(str))
	|| !(split->after = get_after(str)))
	{
		free_struct_folder(split);
		return (false);
	}
	return (true);
}
