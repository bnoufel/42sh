/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:33:46 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:33:48 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				ft_export_exp(t_var **lst, char *line)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = (*lst)->exp;
	if (check_in_list(&(*lst)->lenv, NULL, line, &i))
		return (0);
	while (tmp && tmp->next && (i = ft_strcmp(tmp->elem, line)) != 0)
		tmp = tmp->next;
	if ((*lst)->exp == NULL)
		(*lst)->exp = create_elem(line);
	else if (i != 0 && ft_strcmp(tmp->elem, line) != 0)
		tmp->next = create_elem(line);
	return (0);
}

int				ft_export_loc(t_var **lst, char *to_find, char *line)
{
	int		i;
	t_env	*tmp;
	t_env	*prev;
	t_env	*prev2;

	i = 0;
	prev2 = NULL;
	if ((tmp = check_in_list(&(*lst)->loc, &prev2, to_find, &i)))
	{
		prev = (*lst)->lenv;
		while (prev && prev->next)
			prev = prev->next;
		prev->next = create_elem(tmp->elem);
		if (prev2)
			prev2->next = tmp->next;
		else
			(*lst)->loc = NULL;
		free(tmp);
	}
	else
		ft_export_exp(lst, line);
	return (0);
}

int				ft_export(t_var **lst, char *to_find, char *line, int flag)
{
	int		i;
	t_env	*tmp;
	t_env	*prev;

	i = 0;
	if (flag)
	{
		if ((tmp = check_in_list(&(*lst)->loc, NULL, to_find, &i)))
			ft_strcpy(tmp->elem + i + 1, line + i + 1);
		else if ((tmp = check_in_list(&(*lst)->lenv, &prev, to_find, &i)))
			ft_strcpy(tmp->elem + i + 1, line + i + 1);
		else
		{
			removeifsame(&(*lst)->exp, to_find, &ft_strcmp);
			prev->next = create_elem(line);
		}
		!ft_strcmp(to_find, "PATH") ? create_tab((*lst)->lenv) : 0;
	}
	else
		return (ft_export_loc(lst, to_find, line));
	return (0);
}
