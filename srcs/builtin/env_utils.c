/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:32:10 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:32:12 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void		helprcpenv(t_var **var, int *a, t_env *env)
{
	while (env && env->elem[0])
	{
		if (!((*var)->tenv[*a] = (char *)malloc((ft_strlen(env->elem) + 1)
						* sizeof(char))))
			return ;
		ft_strcpy((*var)->tenv[*a], env->elem);
		env = env->next;
		(*a)++;
	}
}

char			**recpyenv(t_var **root)
{
	t_env	*env;
	t_var	*var;
	int		a;

	var = *root;
	env = var ? var->lenv : 0;
	a = 0;
	while (var && var->tenv && var->tenv[a])
		ft_strdel(&(var->tenv[a++]));
	a = 0;
	if (var)
	{
		free(var->tenv);
		var->tenv = NULL;
	}
	if (!env || !env->elem[0])
		return (0);
	if (!(var->tenv = (char **)malloc((listlen(env) + 1) * sizeof(char *))))
		return (0);
	helprcpenv(&var, &a, env);
	var->tenv[a] = 0;
	return (var->tenv);
}

static	int		createenv(t_av *av, t_env *tmp, t_env *env, t_env **head)
{
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		malloc_failed("createenv");
	ft_bzero(env->elem, sizeof(env->elem));
	env->next = NULL;
	if (!tmp)
		*head = env;
	ft_strlcat(ft_strcat(ft_strcpy(env->elem, av->av), "="),
	av->next->av, LINE_MAX);
	!ft_strcmp(av->av, "PATH") ? create_tab(env) : 0;
	if (tmp)
		tmp->next = env;
	return (0);
}

int				setnewenv(int ac, t_av *av, t_env **head, int a)
{
	t_env	*tmp;
	t_env	*env;

	env = *head;
	tmp = NULL;
	av = av->next;
	if ((ac < 3 || ac > 4) || checkvarname(av->av))
		return (1);
	while (env && env->elem[0])
	{
		if (env_strequ(env->elem, av->av))
		{
			if ((a = 1) && ac == 4 && !ft_strcmp(av->next->next->av, "1"))
			{
				ft_strcpy(env->elem + ft_strlen(av->av) + 1, av->next->av);
				!ft_strcmp(av->av, "PATH") ? create_tab(env) : 0;
			}
			return (0);
		}
		tmp = env;
		env = env->next;
	}
	return ((!a && (ac == 3 || !ft_strcmp(av->next->next->av, "0")
	|| !ft_strcmp(av->next->next->av, "1")))
	? createenv(av, tmp, env, head) : 0);
}

int				unsetenvv(t_par *cur, t_env **env)
{
	int		i;
	char	*av;

	i = 0;
	if (cur->lav->next)
		av = cur->lav->next->av;
	else
		return (1);
	if (cur->ac != 2)
	{
		write(2, "usage: unsetenv [char *NOM]\n", 29);
		return (1);
	}
	while (av[i] != '\0')
	{
		if (av[i] == '=')
		{
			write(2, "usage: unsetenv [char *NOM]\n", 29);
			return (1);
		}
		i++;
	}
	return (ft_list_remove_if(env, av, &env_strequ));
}
