/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:33:41 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:33:42 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

t_env	*create_elem(char *name)
{
	t_env	*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	ft_strcpy(env->elem, name);
	env->next = NULL;
	return (env);
}

int		find_str(char *name, char *find)
{
	int i;

	i = 0;
	while (name[i] == find[i])
		i++;
	if (find[i] == '\0' && (name[i] == '=' || find[i - 1] == '='))
		return (i);
	if (find[i] == '\0' && name[i] == '\0')
		return (i - 1);
	return (-1);
}

int		display_export(t_var **lst, t_par **par, t_av **av)
{
	t_env *tmp;

	tmp = (*lst)->lenv;
	while (tmp)
	{
		ft_putstr("export   ");
		ft_putstr(tmp->elem);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	tmp = (*lst)->exp;
	while (tmp)
	{
		ft_putstr("export   ");
		ft_putstr(tmp->elem);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	(*par)->lav = *av;
	return (0);
}

t_env	*check_in_list(t_env **liste, t_env **prev, char *to_find, int *i)
{
	t_env *tmp;

	tmp = *liste;
	while (tmp && (*i = find_str(tmp->elem, to_find)) == -1)
	{
		if (prev != NULL)
			*prev = tmp;
		tmp = tmp->next;
	}
	if (*i == -1)
		return (NULL);
	return (tmp);
}

int		check_if_fnc(char *line, t_var **lst, int flag)
{
	int		i;
	char	tmp[LINE_MAX];

	i = 0;
	while (line && line[i] && i < LINE_MAX - 1)
	{
		if (line[i] == '=' && i != 0 && flag == 0)
		{
			tmp[i] = '\0';
			if (checkvarname(tmp))
				return (1);
			return (ft_export(lst, tmp, line, 1));
		}
		tmp[i] = line[i];
		i++;
	}
	tmp[i] = '\0';
	return ((!flag && !checkvarname(tmp)) ? ft_export(lst, tmp, line, 0) : 1);
}
