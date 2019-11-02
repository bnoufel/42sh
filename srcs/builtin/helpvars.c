/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpvars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:33:27 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:33:28 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char		**adaptarray(t_var **root)
{
	t_env	*env;
	t_var	*var;
	int		i;

	var = *root;
	env = var->lenv;
	i = 0;
	while (env && var && var->tenv && env->elem[0] && var->tenv[i])
	{
		if (ft_strcmp(env->elem, var->tenv[i]))
			return (recpyenv(root));
		i++;
		env = env->next;
	}
	return ((var && ((env && env->elem[0]) || (var->tenv && var->tenv[i])))
	? recpyenv(root) : var->tenv);
}

int			wstruct(t_var *var, char **cp, int *a, char *tmp)
{
	int	i;

	i = *a;
	if (var->loc && retenv(var->loc, tmp))
		*cp = ft_strjoinfree(*cp, retenv(var->loc, tmp), 1);
	else if (var->lenv && retenv(var->lenv, tmp))
		*cp = ft_strjoinfree(*cp, retenv(var->lenv, tmp), 1);
	else if (var->fnc)
		*cp = ft_strjoinfree(*cp, retenv(var->fnc, tmp), 1);
	tmp[0] ? 0 : (*cp = ft_strjoinfree(*cp, "$", 1));
	*a = (int)ft_strlen(*cp);
	return (*cp && (*cp)[i] ? 0 : 1);
}

int			askpid(char *s, int *i, char **cp, int *a)
{
	char *pid;

	if (s[*i] && s[(*i) + 1] && s[*i] == '$' && s[(*i) + 1] == '$')
	{
		*i += 2;
		pid = lltoa(getpid());
		*cp = substitute(*cp, pid);
		*a = (int)ft_strlen(*cp);
		return (0);
	}
	return (1);
}

char		*bckslshav(char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	*new;

	i = 0;
	j = 0;
	k = (int)ft_strlen(s);
	if (k && k < 2)
	{
		(new = ft_strdup(s)) ? 0 : malloc_failed("bckslshav");
		return (new);
	}
	if (!(new = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		malloc_failed("bckslshav");
	while (s && s[i])
	{
		while (s[i] && ((s[i] == 92 && nbcks(s, i))
		|| (c && s[i] == c && (!i || !nbcks(s, i - 1)))))
			i++;
		s[i] ? new[j++] = s[i++] : 0;
	}
	new[j] = '\0';
	return (new);
}

char		*substitute(char *first, char *last)
{
	char	*new;

	new = first ? ft_strjoin(first, last) : ft_strdup(last);
	ft_strdel(&last);
	ft_strdel(&first);
	return (new);
}
