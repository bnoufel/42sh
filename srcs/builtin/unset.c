/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:33:52 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:33:53 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		add_fnc(t_var **lst, char *name, char *line, int i)
{
	t_env	*tmp;
	char	cpy[PATH_MAX];
	int		k;

	k = 0;
	tmp = (*lst)->fnc;
	(k = (int)ft_strlen(name)) < PATH_MAX - 2 ? ft_strcpy(cpy, name) : 0;
	cpy[k++] = '=';
	cpy[k] = '\0';
	k + (int)ft_strlen(line) - i < PATH_MAX - 1 ? ft_strcpy(cpy + k, line + i)
	: 0;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if ((*lst)->fnc == NULL)
		(*lst)->fnc = create_elem(cpy);
	else
		tmp->next = create_elem(cpy);
	return (0);
}

int		unset(t_par *par, t_var **lst)
{
	t_av *av;

	av = par->lav;
	par->lav = par->lav->next;
	while (par->lav && *lst)
	{
		if ((*lst)->loc)
			ft_list_remove_if(&(*lst)->loc, par->lav->av, &env_strequ);
		if ((*lst)->lenv)
			ft_list_remove_if(&(*lst)->lenv, par->lav->av, &env_strequ);
		if ((*lst)->fnc)
			ft_list_remove_if(&(*lst)->fnc, par->lav->av, &env_strequ);
		if ((*lst)->exp)
			removeifsame(&(*lst)->exp, par->lav->av, &ft_strcmp);
		par->lav = par->lav->next;
	}
	par->lav = av;
	return (0);
}
