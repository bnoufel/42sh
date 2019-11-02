/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpexec2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:07:47 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:07:49 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	freevar(t_var *var)
{
	var && var->lenv ? ft_list_clear(&(var->lenv)) : 0;
	var && var->loc ? ft_list_clear(&(var->loc)) : 0;
	var && var->exp ? ft_list_clear(&(var->exp)) : 0;
	var && var->fnc ? ft_list_clear(&(var->fnc)) : 0;
	if (var && var->tenv)
	{
		ft_free_tab(var->tenv);
		var->tenv = NULL;
	}
	var ? free(var) : 0;
	var = NULL;
}

int		freechild(t_par *cur, t_var *var)
{
	int	i;

	i = 0;
	while (cur->av[i])
		ft_strdel(&(cur->av[i++]));
	free(cur->av);
	cur->av = NULL;
	ft_plist_clear(&cur);
	freevar(var);
	return (1);
}

int		dupinsidefork(t_par *cur, int fd[2])
{
	t_par	*af;
	int		c;

	c = 0;
	af = cur;
	while (af->next && (af->action[0] == '<' || af->action[0] == '>'
	|| ft_isdigit(af->action[0])))
	{
		af->action[0] == '<' ? (c = 1) : 0;
		af = af->next;
	}
	if (!ft_strcmp(af->action, "|") && (!af->prev
	|| ft_atoi(af->prev->action) != 1
	|| af->prev->action[ft_strlen(af->prev->action) - 2] != '>'))
		c ? dup2(fd[1], STDOUT_FILENO) : dup2(cur->fd[1], STDOUT_FILENO);
	return (1);
}

int		toforkornot(t_par *cur, t_var *var, int fd[2])
{
	t_par *start;

	start = cur;
	while (ft_isdigit(cur->action[0]) || !ft_strcmp(cur->action, "|")
	|| cur->action[0] == '<' || cur->action[0] == '>')
	{
		if (!notthisone(cur) && pipe(cur->fd) < 0)
		{
			ft_putendl_fd("mysh: resource temporarily unavailable", 2);
			g_global->sig = 1;
			return (0);
		}
		cur = cur->next;
	}
	cur = start;
	cur->fd[1] && cur->fd[1] > g_global->fdmax
	? (g_global->fdmax = cur->fd[1]) : 0;
	if ((start = cur) && createfds(cur, var, 0, 0))
		return (1);
	if ((cur = start) && nofork(cur))
		g_global->ret = builtin_command(&cur, &var, fd);
	if (dofork(cur, g_global->ret))
		forkaction(cur, var, fd);
	return (0);
}

void	pipensavemax(int fd[2])
{
	if (pipe(fd) < 0)
	{
		ft_putendl_fd("mysh: resource temporarily unavailable", 2);
		g_global->sig = 1;
		return ;
	}
	fd[1] > g_global->fdmax ? g_global->fdmax = fd[1] : 0;
}
