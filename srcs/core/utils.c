/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:59:52 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:15 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			fillav(t_par *cur, char *buf, int e, int s)
{
	t_av *new;

	new = cur->lav->last;
	if (!(new->next = (t_av *)malloc(sizeof(t_av))))
		malloc_failed("newav");
	new->next->av = ft_strsub(buf, s, e - s);
	new->next->head = new->head;
	new->next->last = new->next;
	new->last = new->next->last;
	new->next->prev = new;
	new = new->next;
	new->next = NULL;
	cur->lav->last = new->last;
}

static char		*ft_getnameenv(char **env, int i)
{
	int			j;
	char		*name;

	j = 0;
	if (!(name = (char *)ft_strnew(PATH_MAX)))
		malloc_failed("ft_nameenv");
	while (env[i][j])
	{
		if (env[i][j] == '=')
			break ;
		name[j] = env[i][j];
		j++;
	}
	return (name);
}

char			*ft_getenv(char *search, t_var **var)
{
	int			i;
	char		*value;
	char		*name;
	char		**env;

	env = (*var)->tenv;
	i = 0;
	if (!search)
		return (NULL);
	while (env[i])
	{
		name = ft_getnameenv(env, i);
		value = ft_strchr(env[i], '=');
		if (ft_strcmp(name, search) == 0)
		{
			free(name);
			return (value + 1);
		}
		free(name);
		i++;
	}
	return (NULL);
}

char			*transform_tab_to_char(char **temp)
{
	char		*tmp;
	int			i;

	i = 0;
	if (!(tmp = ft_strnew(0)))
		malloc_failed("transform_tab_to_char");
	while (temp[i])
	{
		if (i && !(tmp = ft_strjoinfree(tmp, " ", 1)))
			malloc_failed("transform_tab_to_char");
		if (!(tmp = ft_strjoinfree(tmp, temp[i], 1)))
			malloc_failed("transform_tab_to_char");
		i++;
	}
	return (tmp);
}

char			*transform_list_to_char(t_av *temp)
{
	char		*tmp;

	if (!(tmp = ft_strnew(0)))
		malloc_failed("transform_list_to_char");
	while (temp)
	{
		if (temp->av && !(tmp = ft_strjoinfree(tmp, temp->av, 1)))
			malloc_failed("transform_list_to_char");
		if (temp->next && !(tmp = ft_strjoinfree(tmp, " ", 1)))
			malloc_failed("transform_list_to_char");
		temp = temp->next;
	}
	return (tmp);
}
