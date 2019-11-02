/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:38:01 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/19 11:22:56 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void			join_hook2(t_split *split, char **temp, int i, int ec[3])
{
	if (ec[1] && ec[1] >= ec[0])
	{
		if (!(*temp = ft_strjoinfree(split->before,
						ft_chardup((char)ec[0]), 2)))
			malloc_failed("join_hook");
		if (!(*temp = ft_strjoinfree(*temp, split->after, 1)))
			malloc_failed("join_hook");
		ec[0] = ec[0] + 1;
	}
	else
	{
		if (!(*temp = ft_strjoinfree(split->before,
						ft_strsub(split->middle, i, 1), 2)))
			malloc_failed("join_hook");
		if (!(*temp = ft_strjoinfree(*temp, split->after, 1)))
			malloc_failed("join_hook");
	}
}

static int			helptojoin(char **temp, int *r, char **temp2)
{
	t_par	*spl;
	t_av	*save;

	if (*temp && (g_global->par = 2))
	{
		*temp = ft_strjoinfree(*temp, " ", 1);
		parseline(temp, &spl);
		ft_strdel(temp);
		save = spl->lav;
		while (spl->lav && (*temp = bckslshav(spl->lav->av,
		chardelim(spl->lav->av))))
		{
			if (check_hook_file_exist(*temp) && (*temp2 = ft_strjoinfree(*temp2,
			ft_strjoin(spl->lav->av, " "), 3)))
				*r = 1;
			ft_strdel(temp);
			spl->lav = spl->lav->next;
		}
		spl->lav = save;
		ft_plist_clear(&spl);
		return (0);
	}
	return (1);
}

static char			*cleanhook(char *toclean, int i, int j, int k)
{
	char	toret[95];

	ft_bzero(toret, sizeof(toret));
	while (toclean[i])
	{
		j = 0;
		k = 0;
		while (toret[k] && k < 94)
		{
			if (toclean[i] && toret[k] == toclean[i] && (j = 1))
				break ;
			k++;
		}
		if (!j && toclean[i] && k < 94)
		{
			toret[k++] = toclean[i++];
			toret[k] = '\0';
		}
		else if (j && toclean[i])
			i++;
	}
	ft_strdel(&toclean);
	return (ft_strdup(toret));
}

static char			*join_hook(t_split *split, int *r, int ec[3], t_var *var)
{
	char			*temp;
	char			*temp2;
	int				i;
	int				j;
	char			*tofree;

	i = 0;
	temp = NULL;
	temp2 = NULL;
	if (ec[1] && ec[1] >= ec[0])
		i = (int)ft_strlen(split->middle);
	else
		split->middle = cleanhook(split->middle, 0, 0, 0);
	while ((j = 1) && (split->middle[i] || (ec[1] && ec[1] >= ec[0])))
	{
		split->middle[i] && split->middle[i] == '\\' && !nbcks(split->middle, i)
			? i++ : 0;
		join_hook2(split, &temp, i, ec);
		while (j && (tofree = temp))
			temp = glob_core_while(temp, &j, var, 1);
		helptojoin(&temp, r, &temp2) ? ft_strdel(&tofree) : 0;
		g_global->par = 0;
		split->middle[i] ? i++ : 0;
	}
	return (temp2);
}

char				*hook_parser(char **str, int *j, t_var *var)
{
	char			*tmp;
	t_split			split;
	int				ec[3];

	tmp = NULL;
	if (!split_folder_hook(&split, *str, ec))
		return (NULL);
	tmp = join_hook(&split, j, ec, var);
	free_struct_folder(&split);
	if (tmp)
	{
		ft_strdel(str);
		*str = tmp;
	}
	return (*str);
}
