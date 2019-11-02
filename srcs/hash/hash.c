/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:42 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:42 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	clean_tab(void)
{
	t_hash	*bucket;
	t_bin	*tmp;

	tmp = g_global->bin;
	if (!g_global->buckets)
		return ;
	while (tmp)
	{
		while (g_global->buckets && g_global->buckets[tmp->hash])
		{
			bucket = g_global->buckets[tmp->hash];
			g_global->buckets[tmp->hash] = g_global->buckets[tmp->hash]->next;
			ft_strdel(&bucket->name);
			ft_strdel(&bucket->path);
			free(bucket);
			bucket = NULL;
		}
		tmp = tmp->next;
	}
	free(g_global->buckets);
	g_global->buckets = NULL;
}

void	clean_bin(void)
{
	t_bin	*tmp;
	t_bin	*bin;

	bin = g_global->bin;
	if (!bin)
		return ;
	while (bin)
	{
		tmp = bin;
		bin = bin->next;
		ft_strdel(&tmp->path);
		ft_strdel(&tmp->name);
		free(tmp);
		tmp = NULL;
	}
	g_global->bin = NULL;
}

void	init_buckets(size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		g_global->buckets[i] = NULL;
		i++;
	}
	g_global->buckets[i] = NULL;
}

char	*get_hash(char *bin)
{
	t_hash	*buckets;
	size_t	bsize;
	size_t	get_hash;

	get_hash = hash(bin);
	bsize = ft_size_bin(g_global->bin);
	if (bsize == 0 || get_hash > bsize)
		return (NULL);
	if (!(buckets = g_global->buckets[get_hash]))
		return (NULL);
	while (buckets)
	{
		if (ft_strcmp(buckets->name, bin) == 0)
			return (buckets->path);
		buckets = buckets->next;
	}
	return (NULL);
}

t_hash	**create_tab(t_env *env)
{
	t_bin	*bin;
	size_t	bsize;

	clean_tab();
	clean_bin();
	get_binaries(&(g_global->bin), env);
	bin = g_global->bin;
	if (bin)
		ft_putendl("Hash table reset [\033[32m✔\033[0m]");
	else
	{
		ft_putstr_fd("\033[31m/!\\\033[0m Hash table empty", 2);
		ft_putendl_fd(", please set a valid path", 2);
	}
	bsize = ft_size_bin(g_global->bin);
	(g_global->buckets = (t_hash **)malloc(sizeof(t_hash *) * (bsize + 1)))
	? 0 : malloc_failed("create_tab");
	init_buckets(bsize);
	while (bin)
	{
		g_global->buckets[hash(bin->name)] = ft_create_elem_hash(
		g_global->buckets[hash(bin->name)], bin->name, bin->path);
		bin = bin->next;
	}
	return (g_global->buckets);
}
