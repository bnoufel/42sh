/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equalizer_check_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:01:16 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:02:32 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

/*
** @brief
** -p : le fichier est un tube nommé
** -t : le fichier (descripteur) est associé avec un terminal
** @param cmp
** @param st
** @return
*/

static bool			check_if_is_a_spec_file3(t_cmp *cmp)
{
	int				fd;
	t_stat			st;

	if (!ft_strcmp(cmp->cmp, "-p"))
	{
		if (cmp->isnot && stat(cmp->str, &st) == -1)
			return (S_ISFIFO(st.st_mode));
		else if (cmp->isnot < 1 && stat(cmp->str, &st) != -1)
			return (S_ISFIFO(st.st_mode));
	}
	else if (!ft_strcmp(cmp->cmp, "-t"))
	{
		if (cmp->isnot < 1 && cmp->str_is_integer)
		{
			fd = ft_atoi(cmp->str);
			if (fd == STDIN_FILENO || fd == STDOUT_FILENO
				|| fd == STDERR_FILENO)
				return (true);
			return (false);
		}
		cmp->error = -17;
		return (false);
	}
	return (false);
}

/*
** @brief
** -b : le fichier est un périphérique de type bloc
** -c : le fichier est un périphérique de type caractère
** -h & -L : le fichier est un lien symbolique
** @param cmp
** @param st
** @return
*/

static bool			check_if_is_a_spec_file2(t_cmp *cmp)
{
	t_stat			st;

	if (!ft_strcmp(cmp->cmp, "-b"))
	{
		if ((cmp->isnot && stat(cmp->str, &st) == -1)
			|| (cmp->isnot < 1 && stat(cmp->str, &st) != -1))
			return (S_ISBLK(st.st_mode));
	}
	else if (!ft_strcmp(cmp->cmp, "-c"))
	{
		if (cmp->isnot && stat(cmp->str, &st) == -1)
			return (S_ISCHR(st.st_mode));
		else if (cmp->isnot < 1 && stat(cmp->str, &st) != -1)
			return (S_ISCHR(st.st_mode));
	}
	else if (!ft_strcmp(cmp->cmp, "-h") || !ft_strcmp(cmp->cmp, "-L"))
	{
		if (cmp->isnot && stat(cmp->str, &st) == -1)
			return (S_ISLNK(st.st_mode));
		else if (cmp->isnot < 1 && stat(cmp->str, &st) != -1)
			return (S_ISLNK(st.st_mode));
	}
	else
		return (check_if_is_a_spec_file3(cmp));
	return (false);
}

/*
** @brief
** -f : le fichier est un fichier ordinaire
** -d :le fichier est un répertoire
** -S : le fichier est un socket
** @param cmp
** @param st
** @return
*/

bool				check_if_is_a_spec_file(t_cmp *cmp)
{
	t_stat			st;

	if (!ft_strcmp(cmp->cmp, "-f"))
	{
		if ((cmp->isnot && stat(cmp->str, &st) == -1)
		|| (cmp->isnot < 1 && stat(cmp->str, &st) != -1))
			return (S_ISREG(st.st_mode));
	}
	else if (!ft_strcmp(cmp->cmp, "-d"))
	{
		if (cmp->isnot && stat(cmp->str, &st) == -1)
			return (S_ISDIR(st.st_mode));
		else if (cmp->isnot < 1 && stat(cmp->str, &st) != -1)
			return (S_ISDIR(st.st_mode));
	}
	else if (!ft_strcmp(cmp->cmp, "-S"))
	{
		if (cmp->isnot && stat(cmp->str, &st) == -1)
			return (S_ISSOCK(st.st_mode));
		else if (cmp->isnot < 1 && stat(cmp->str, &st) != -1)
			return (S_ISSOCK(st.st_mode));
	}
	else
		return (check_if_is_a_spec_file2(cmp));
	return (false);
}

/*
** @brief
** -a & -e : le fichier existe
** @param cmp
** @param st
** @return
*/

bool				check_file_exist(t_cmp *cmp)
{
	t_stat			st;

	if (!ft_strcmp(cmp->cmp, "-e") || !ft_strcmp(cmp->cmp, "-a"))
	{
		if (cmp->isnot < 1 && stat(cmp->str1, &st) != -1)
			return (true);
		else if (cmp->isnot && stat(cmp->str1, &st) == -1)
			return (true);
		return (false);
	}
	return (false);
}

/*
** @brief
** -s : le fichier a une taille supérieure à zéro
** @param cmp
** @param st
** @return
*/

bool				check_if_file_no_empty(t_cmp *cmp)
{
	t_stat			st;

	if (!ft_strcmp(cmp->cmp, "-s") && stat(cmp->str, &st) != -1)
	{
		if (!cmp->isnot && st.st_size > 0)
			return (true);
		else if (cmp->isnot && st.st_size == 0)
			return (true);
	}
	return (false);
}
