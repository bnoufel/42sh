/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equalizer_check_file2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:59:56 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:27 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

/*
** @brief
** -N : le fichier a été modifié depuis sa dernière lecture
** @param cmp
** @param st
** @return
*/

static bool			check_file_right3(t_cmp *cmp, t_stat st)
{
	if (!ft_strcmp(cmp->cmp, "-N") && stat(cmp->str, &st) != -1)
	{
		if (cmp->isnot < 1 && &st.st_mtime > &st.st_atime)
			return (true);
		else if (cmp->isnot && &st.st_mtime <= &st.st_atime)
			return (false);
	}
	return (false);
}

/*
** @brief check right of file (-g -u -k)
** -g : le file dispose du droit set-group-id (sgid) sur ce fichier ou dossier
** -u : le fichier dispose du droit set-user-id
** -k : sticky bit mis
** @param cmp
** @param st
** @return
*/

static bool			check_file_right2(t_cmp *cmp, t_stat st)
{
	if (!ft_strcmp(cmp->cmp, "-g") && stat(cmp->str, &st) != -1)
	{
		if (cmp->isnot && !(st.st_mode & S_ISGID))
			return (true);
		else if (cmp->isnot < 1 && (st.st_mode & S_ISGID))
			return (true);
		return (false);
	}
	else if (!ft_strcmp(cmp->cmp, "-u") && stat(cmp->str, &st) != -1)
	{
		if (cmp->isnot && !(st.st_mode & S_ISUID))
			return (true);
		else if (cmp->isnot < 1 && (st.st_mode & S_ISUID))
			return (true);
		return (false);
	}
	else if (!ft_strcmp(cmp->cmp, "-k") && stat(cmp->str, &st) != -1)
	{
		if (cmp->isnot && !(st.st_mode & S_ISVTX))
			return (true);
		else if (cmp->isnot < 1 && (st.st_mode & S_ISVTX))
			return (true);
		return (false);
	}
	return (check_file_right3(cmp, st));
}

/*
** @brief
** -G : vous faites partie du groupe propriétaire du fichier
** @param cmp
** @param st
** @return
*/

static bool			check_file_right_grp(t_cmp *cmp, t_stat st)
{
	t_group			*user;
	t_group			*mine;

	if (!ft_strcmp(cmp->cmp, "-G") && stat(cmp->str, &st) != -1)
	{
		mine = getgrgid(getgid());
		user = getgrgid(st.st_gid);
		if (!mine || !user)
		{
			if (getgid() == st.st_gid)
				return ((!cmp->isnot) ? true : false);
			return ((!cmp->isnot) ? false : true);
		}
		if (!ft_strcmp(mine->gr_name, user->gr_name))
			return ((!cmp->isnot) ? true : false);
		return (false);
	}
	else
		return (check_file_right2(cmp, st));
}

/*
** @brief
** -O : vous êtes le propriétaire du fichier
** @param cmp
** @param st
** @return
*/

static bool			check_file_right_user(t_cmp *cmp, t_stat st)
{
	t_passwd		*user;
	t_passwd		*mine;

	if (!ft_strcmp(cmp->cmp, "-O") && stat(cmp->str, &st) != -1)
	{
		mine = getpwuid(getuid());
		user = getpwuid(st.st_uid);
		if (!mine || !user)
		{
			if (getuid() == st.st_uid)
				return ((!cmp->isnot) ? true : false);
			return ((!cmp->isnot) ? false : true);
		}
		if (!ft_strcmp(mine->pw_name, user->pw_name))
			return ((!cmp->isnot) ? true : false);
		return (false);
	}
	else
		return (check_file_right_grp(cmp, st));
}

/*
** @brief check right of file (-r -w -x)
** -r : le fichier dispose du droit de lecture pour l'user
** -w : le fichier dispose du droit d'écriture pour l'user
** -x : le fichier dispose du droit d'exécution pour l'user
** @param cmp
** @param st
** @return
*/

bool				check_file_right(t_cmp *cmp)
{
	t_stat			st;

	if (!ft_strcmp(cmp->cmp, "-r") && stat(cmp->str, &st) != -1)
	{
		if ((!cmp->isnot && (st.st_mode & S_IRUSR))
		|| (cmp->isnot && !(st.st_mode & S_IRUSR)))
			return (true);
	}
	else if (!ft_strcmp(cmp->cmp, "-w") && stat(cmp->str, &st) != -1)
	{
		if (!cmp->isnot && (st.st_mode & S_IWUSR))
			return (true);
		else if (cmp->isnot && !(st.st_mode & S_IWUSR))
			return (true);
	}
	else if (!ft_strcmp(cmp->cmp, "-x") && stat(cmp->str, &st) != -1)
	{
		if (!cmp->isnot && (st.st_mode & S_IXUSR))
			return (true);
		else if (cmp->isnot && !(st.st_mode & S_IXUSR))
			return (true);
	}
	else
		return (check_file_right_user(cmp, st));
	return (false);
}
