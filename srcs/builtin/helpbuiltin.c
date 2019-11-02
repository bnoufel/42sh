/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpbuiltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:32:46 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:32:48 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void		tpath(char *paths, char **p, int *a, int *i)
{
	while ((*p) && paths[*i] && paths[*i] != ':')
	{
		(*p)[*a] = paths[*i];
		(*i)++;
		(*a)++;
	}
	paths[*i] ? (*i)++ : 0;
	(*p)[*a] != '/' ? (*p)[(*a)++] = '/' : 0;
	(*p)[*a] = '\0';
}

char			*cdpath(char *paths, char *cmd)
{
	char	*p;
	int		i;
	int		a;

	i = 0;
	a = 0;
	if (!(p = (char *)malloc(sizeof(char)
		* ((ft_strlen(paths) + ft_strlen(cmd) + 4)))))
		malloc_failed("cdpath");
	ft_bzero(p, sizeof(p));
	while (paths[i])
	{
		tpath(paths, &p, &a, &i);
		ft_strcat(p, cmd);
		if (access(p, X_OK) == 0)
		{
			ft_strdel(&paths);
			return (p);
		}
		else if (!(a = 0))
			ft_bzero(p, sizeof(p));
	}
	ft_strdel(&p);
	ft_strdel(&paths);
	return (0);
}

void			startfromroot(char **s)
{
	char	*af;
	int		i;

	i = 0;
	while ((*s)[i] && ((*s)[i] == '.' || (*s)[i] == '/'))
		i++;
	(af = ft_strdup(*s + i)) ? 0 : malloc_failed("startfromroot");
	(*s)[1] = '\0';
	*s = substitute(*s, af);
	handledots(s, 0, 0, ft_strlen(*s));
}
