/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_autocompl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:06:50 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:06:54 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char			*ac_take_before(char *str, int index)
{
	char			*before;
	int				i;

	i = 0;
	if (!(before = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		malloc_failed("ac_take_before");
	while (index > 0 && str[index])
	{
		if (str[index] == ' ' && str[index - 1] != '\\')
			break ;
		index--;
	}
	while (i < (index + 1) && str[i])
	{
		before[i] = str[i];
		i++;
	}
	before[i] = '\0';
	return (before);
}

static char			*ac_take_middle(char *str, int i)
{
	char			*middle;
	int				j;

	j = 0;
	if (!(middle = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		malloc_failed("ac_take_middle");
	while (i >= 0)
	{
		if (i == 0 && str[i] == ' ')
			break ;
		if (i > 0 && str[i] == ' ' && str[i - 1] && str[i - 1] != '\\')
			break ;
		i--;
	}
	++i;
	while (str[i])
	{
		if (str[i] == ' ' && str[i - 1] != '\\')
			break ;
		middle[j] = str[i];
		j++;
		i++;
	}
	middle[j] = '\0';
	return (middle);
}

static char			*ac_take_after(char *str, int index)
{
	char			*after;
	int				i;

	i = 0;
	if (!(after = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		malloc_failed("ac_take_after");
	while (str[index] != ' ')
		index++;
	while (str[index])
	{
		after[i] = str[index];
		index++;
		i++;
	}
	after[i] = '\0';
	return (after);
}

t_split				*ac_init_struct(char *str, int index)
{
	t_split			*autocompl;

	if (!(autocompl = (t_split *)malloc(sizeof(t_split) * 3)))
		malloc_failed("ac_init_struct");
	autocompl->before = ac_take_before(str, index);
	autocompl->middle = ac_take_middle(str, index);
	autocompl->after = ac_take_after(str, index);
	return (autocompl);
}
