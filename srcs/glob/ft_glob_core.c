/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:37:56 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/19 11:57:01 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char		*matchmessage(int c, char *str)
{
	if (!c)
	{
		ft_putstr_fd("mysh: no matches found: ", 2);
		ft_putendl_fd(str, 2);
	}
	return (NULL);
}

char			*glob_core_while(char *str, int *j, t_var *var, int c)
{
	static int r;

	*j = 0;
	r = !c ? 0 : r + 1;
	if (r > 255 && !(*j = 0))
		return (NULL);
	if (schrnob(str, '[') && hook_parser(&str, j, var) && !(*j))
		return (matchmessage(c, str));
	else if (schrnob(str, '{') && braces_parser(&str, j) && (!(*j) || r > 2))
		return (NULL);
	else if ((schrnob(str, '?') || schrnob(str, '*'))
			&& star_parser(&str, j) && !(*j))
		return (matchmessage(c, str));
	return (str);
}

char			*schrnob(char *s, char c)
{
	int i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c && (!i || !nbcks(s, i - 1))
				&& !quoted(s, i) && (c != '[' || s[i + 1] != ' '))
			return (s + i);
		i++;
	}
	if (s[i] == c && !nbcks(s, i))
		return (s + i);
	return (NULL);
}

bool			check_hook_file_exist(char *str)
{
	DIR			*odir;
	t_dirent	*rdir;

	if (!(odir = opendir(".")))
		return (false);
	while ((rdir = readdir(odir)))
	{
		if (!ft_strcmp(rdir->d_name, str))
		{
			closedir(odir);
			return (true);
		}
	}
	closedir(odir);
	return (false);
}
