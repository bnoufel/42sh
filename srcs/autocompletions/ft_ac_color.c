/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ac_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:06:01 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:06:04 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int		ft_is_rw(mode_t mode)
{
	if ((mode & S_IRUSR) && (mode & S_IWUSR)
	&& (mode & S_IRGRP) && (mode & S_IWGRP)
	&& (mode & S_IROTH) && (mode & S_IWOTH))
		return (1);
	return (0);
}

static int		ft_danger(mode_t mode)
{
	if ((mode & S_IRUSR) && (mode & S_IWUSR)
	&& (mode & S_IXUSR) && (mode & S_IRGRP)
		&& (mode & S_IWGRP) && (mode & S_IXGRP)
		&& (mode & S_IROTH) && (mode & S_IWOTH)
		&& (mode & S_IXOTH))
		return (1);
	return (0);
}

static char		*ft_color2(mode_t mode, char *color)
{
	if (S_ISLNK(mode))
		color = CYAN;
	else if (S_ISFIFO(mode))
		color = MAGENTA;
	else if (S_ISBLK(mode))
		color = GREEN;
	else if (S_ISSOCK(mode))
		color = YELLOW;
	else if (S_ISCHR(mode))
		color = YELLOW;
	return (color);
}

char			*ft_ac_color(mode_t mode)
{
	char		*color;

	color = RESET;
	if (S_ISDIR(mode))
	{
		if (ft_is_rw(mode) || ft_danger(mode))
			color = BGGREEN;
		else
			color = RED;
	}
	else if (S_ISREG(mode))
	{
		if (mode & S_ISUID || mode & S_ISGID)
			color = BGRED;
		else if (mode & S_IXOTH || mode & S_IXUSR || mode & S_IXGRP)
			color = GREEN;
		else
			color = RESET;
	}
	else
		color = ft_color2(mode, color);
	return (color);
}
