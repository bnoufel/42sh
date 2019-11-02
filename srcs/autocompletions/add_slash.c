/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_slash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:04:46 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:04:51 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char			*ft_remove_back(char *str)
{
	int				i;

	i = 0;
	while (str[i] && str[i] != '\\')
		i++;
	if (i == (int)ft_strlen(str))
		return (str);
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	return (str);
}

static int			ft_is_dir(char *str)
{
	t_stat			sta;
	char			*new;
	int				i;

	i = 0;
	if (!(new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (-1);
	while (str[i] && ((str[i] == ' ' && str[i - 1] == '\\') || (str[i] != ' ')))
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	new = ft_remove_back(new);
	if (stat(new, &sta) == -1)
	{
		free(new);
		return (-1);
	}
	free(new);
	if (sta.st_mode & S_IFDIR)
		return (1);
	return (0);
}

static char			*ft_realloc_slash(char *str, int number)
{
	int				i;
	int				j;
	char			*new;

	if (!(new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2))))
		malloc_failed("realloc_slash");
	j = 0;
	i = 0;
	while (str[i])
	{
		if (i + j == number + 1)
			new[i + j++] = '/';
		else
		{
			new[i + j] = str[i];
			i++;
		}
	}
	if (new[i] == ' ')
		new[i] = '\0';
	else
		new[i + j] = '\0';
	return (new);
}

int					ft_add_slash(char *str, int n, t_list **list, t_cursor *c)
{
	int				i;
	char			*new;
	int				a;

	i = n;
	if (str[n] == '/' || str[n] == ' ')
		return (0);
	while (i > 0 && ((str[i - 1] == ' '
					&& str[i - 2] == '\\') || (str[i - 1] != ' ')))
		i--;
	if ((a = ft_is_dir(str + i)) == 1)
	{
		new = ft_realloc_slash(str, n);
		ft_str_to_list(new, list);
		c->completion = 0;
		free(new);
		return (1);
	}
	return (0);
}
