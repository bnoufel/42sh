/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helptoparse5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:39:52 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:39:53 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	changelast(t_av **take, t_av **give)
{
	t_av *iter;

	iter = *take;
	{
		while (iter)
		{
			iter->last = (*give)->last;
			iter = iter->next;
		}
	}
}

void	changehead(t_av **take, t_av **give)
{
	t_av *iter;

	iter = *take;
	while (iter)
	{
		iter->head = (*give)->head;
		iter = iter->next;
	}
}

int		hckp(char *s, int i)
{
	while (i && s[i] == 40)
		i--;
	if (s[i] == '$' && (!i || !nbcks(s, i - 1)))
		return (1);
	return (0);
}

int		outofrecfd(char **s, int *p, char c, t_par *cur)
{
	char *new;

	new = NULL;
	if (!(*p = 0) && ((g_global->stdi && !gnl(0, &new, 1))
	|| g_global->sub
	|| (g_global->is_scrpt && !gnl(g_global->f_fd, &new, 1))) && (*p = 1))
	{
		ft_putstr_fd("mysh: ", 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd(" unmatched\n", 2);
		return (0);
	}
	else if ((g_global->stdi || g_global->is_scrpt) && (*p = 1))
	{
		if (c != 34 && c != 39 && !cur->math
		&& !(*s = ft_strjoinfree(*s, ft_strjoinfree(";", new, 2), 3)))
			malloc_failed("outofrec");
		else if ((c == 34 || c == 39)
		&& !(*s = ft_strjoinfree(*s, ft_strjoinfree("\n", new, 2), 3)))
			malloc_failed("outofrec");
		else if (c == 41 && cur->math
		&& !(*s = ft_strjoinfree(*s, ft_strjoinfree(" ", new, 2), 3)))
			malloc_failed("outofrec");
	}
	return (1);
}

int		onlyspaces(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
