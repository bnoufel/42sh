/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpscript.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:09:01 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:09:02 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	help_clause_2(char **tosplit, t_par **temp, t_var **var)
{
	g_global->par = 2;
	parseline(tosplit, temp);
	g_global->par = 0;
	rewriteavs(temp, *var, 0, 0);
}

char	**helpforclause(char *s, t_var **var)
{
	t_par	*temp;
	char	*tosplit;
	char	**ret;
	t_av	*save;
	int		i;

	i = 0;
	temp = NULL;
	if (!(tosplit = ft_strjoin(s, " ")))
		malloc_failed("helpforclause");
	help_clause_2(&tosplit, &temp, var);
	save = temp->lav;
	ft_strdel(&tosplit);
	if (!(ret = (char **)malloc((temp->ac + 1) * sizeof(char *))))
		malloc_failed("helpforclause");
	while (temp->lav)
	{
		!(ret[i++] = ft_strdup(temp->lav->av)) ?
		malloc_failed("helpforclause") : 0;
		temp->lav = temp->lav->next;
	}
	temp->lav = save;
	ret[i] = 0;
	ft_plist_clear(&temp);
	return (ret);
}
