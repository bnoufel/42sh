/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:43 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:00:44 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void			init_term2(t_cursor *cursor, int n, t_var **var)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		exit_term(var);
	if (n == 1)
	{
		if (!(cursor->old = (struct termios *)malloc(sizeof(struct termios))))
			return (malloc_failed("init_term2"));
		if (tcgetattr(0, cursor->old) == -1)
			malloc_failed("12");
	}
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VSTOP] = 0;
	term.c_cc[VSTART] = 0;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		malloc_failed("init_term2");
	ft_putstr_fd("\x1b[?25l", 0);
}

static void		ft_after_enter(t_list **list, t_cursor *cursor, t_var **v)
{
	cursor->job = 0;
	if (g_pgid)
		tcsetpgrp(0, g_pgid->new_pgid);
	init_term2(cursor, 0, v);
	g_global->prefix = 0;
	while ((*list)->prev)
		*list = (*list)->prev;
	if (g_global->sig != 1)
		ft_putstr_fd("\n", 0);
	while ((*list)->next->next)
		ft_free_right_node(list);
	init_cursor(cursor, 0);
}

static void		ft_before_enter(t_cursor *cursor, t_list *first, t_var **v)
{
	g_global->bg = 0;
	count_and_erase_line(cursor, first, 3);
	ft_info_line(cursor, v);
	ft_read_list(first, cursor, 0);
	ft_putendl_fd("", 0);
	if (tcsetattr(0, TCSANOW, cursor->old) == -1)
		ft_bye_bye(v, 0, NULL, 1);
}

static void		ft_is_jobs(char *str, int *jobs)
{
	int			i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
	{
		*jobs = 0;
		return ;
	}
	if (ft_strncmp(str, "jobs", 4) == 0)
		*jobs = 1;
	else
		*jobs = 0;
}

void			ft_enter(t_list **list, t_cursor *cursor, t_list *f, t_var **v)
{
	char		*str;
	int			jobs;

	jobs = 0;
	ft_before_enter(cursor, f, v);
	str = ft_list_to_string(*list, 1);
	ft_built_in_exc(&str);
	if (str)
	{
		ft_is_jobs(str, &jobs);
		if (ft_check_before_launch(&str))
		{
			if (ft_check_before_2(&str))
			{
				g_global->ret = eval(&str, v);
				ft_hist_next(cursor, f, *list);
			}
			else
				ft_putstr_fd("fun_sh : name too long\n", 2);
		}
		else
			ft_putstr_fd("fun_sh : argument list too long\n", 2);
	}
	ft_after_enter(list, cursor, v);
	ft_after_command_job(jobs);
}
