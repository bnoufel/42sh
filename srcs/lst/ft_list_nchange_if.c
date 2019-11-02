/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_nchange_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:46 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:47 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			find_char(char *str, char c)
{
	int i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	helplnci(int (*equ)(), t_env **tmp, t_env **list,
				char *data_ref)
{
	char	*ref;
	int		i;

	*tmp = NULL;
	i = find_char(data_ref, '=');
	ref = i >= 0 ? ft_strsub(data_ref, 0, i) : NULL;
	while (*list)
	{
		if (equ((*list)->elem, ref))
		{
			ft_bzero((*list)->elem, sizeof((*list)->elem));
			ft_strcpy((*list)->elem, data_ref);
			!ft_strcmp(ref, "PATH") ? create_tab(*list) : 0;
			ft_strdel(&ref);
			return (1);
		}
		*tmp = *list;
		*list = (*list)->next;
	}
	ft_strdel(&ref);
	return (0);
}

static char	*findinexp(t_env *env, char *occur)
{
	while (env)
	{
		if (!ft_strcmp(env->elem, occur))
			return (env->elem);
		env = env->next;
	}
	return (0);
}

int			ft_list_nchange_if(t_var **var, char *data_ref,
				int (*equ)(), int n)
{
	t_var	*ref;
	t_env	*list;
	t_env	*tmp;
	char	t[PATH_MAX];

	ref = *var;
	*(ft_strchr(ft_strcpy(t, data_ref), '=')) = '\0';
	list = n >= 0 || findinexp((*var)->exp, t) ? ref->lenv : ref->loc;
	if (helplnci(&env_strequ, &tmp, &list, data_ref) == 1)
		return (0);
	if (!n)
		return (ft_list_nchange_if(var, data_ref, equ, -1));
	if (!(list = (t_env *)malloc(sizeof(t_env))))
		malloc_failed("ft_list_nchange_if");
	list->next = NULL;
	ft_strcpy(list->elem, data_ref);
	(n >= 0 || findinexp((*var)->exp, t)) && env_strequ(list->elem, "PATH")
	? create_tab(list) : 0;
	if (tmp)
		tmp->next = list;
	else if (n < 0 && !findinexp((*var)->exp, t))
		ref->loc = list;
	else
		ref->lenv = list;
	return (0);
}
