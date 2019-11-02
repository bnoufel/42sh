/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:59:19 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:02:01 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void				init_term(t_cursor *cursor, int n, t_var **var, int job)
{
	struct termios	term;
	int				shell_pgid;
	int				shell_is_interactive;
	int				o_pgid;

	if (tcgetattr(0, &term) == -1 && term2(var))
		exit_term(var);
	if (job == 1 && term1(&shell_pgid, &shell_is_interactive, &o_pgid))
		exit_term(var);
	if (n == 1)
	{
		if (!(cursor->old = (struct termios *)malloc(sizeof(struct termios))))
			return (malloc_failed("init_term"));
		if (tcgetattr(0, cursor->old) == -1)
			malloc_failed("12");
	}
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VSTOP] = 0;
	term.c_cc[VSTART] = 0;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		malloc_failed("init_term");
	ft_putstr_fd("\x1b[?25l", 0);
}

void				init_cursor(t_cursor *cursor, int n)
{
	cursor->col = 1;
	cursor->color = 6;
	cursor->is_selected = 0;
	cursor->search = 0;
	cursor->completion = 0;
	cursor->res_search = -1;
	cursor->job = 0;
	if (n == 1)
		cursor->save = NULL;
}

static int			file_to_eval(t_var **var)
{
	char			*tmp;
	int				i;
	int				read_state;

	i = 0;
	tcsetpgrp(g_global->f_fd, getpid());
	while (++i < 32)
		signal(i, SIG_DFL);
	signal(SIGINT, sig_h);
	while ((read_state = gnl(g_global->f_fd, &tmp, 1)) > 0)
	{
		if (skip_comment(&tmp) != 2)
			eval(&tmp, var);
	}
	close(g_global->f_fd);
	return (read_state);
}

t_var				*init_var(void)
{
	extern char		**environ;
	t_var			*var;
	char			pw[PATH_MAX];

	if (!(g_global->spwd = (t_dir *)malloc(sizeof(t_dir))))
		malloc_failed("init_g");
	ft_strcpy(pw, ".");
	ft_strcpy(g_global->spwd->pwd, getcwd(pw, sizeof(pw)));
	if (!(var = (t_var *)malloc(sizeof(t_var))))
		malloc_failed("ft_realloc_term");
	var->loc = NULL;
	var->exp = NULL;
	var->fnc = NULL;
	if (!(var->tenv = ft_sstrdup(environ)))
		malloc_failed("init_var");
	var->lenv = copyenv(environ, var, 0, 0);
	return (var);
}

void				init_g(t_var **var, int ac, char **av, t_cursor **cursor)
{
	if (!(g_global->pid = (t_pid *)malloc(sizeof(t_pid))))
		malloc_failed("init_g");
	g_global->prefix = false;
	g_global->pid->pid = getpid();
	g_global->pid->next = NULL;
	g_global->ck = NULL;
	g_global->cmdline = NULL;
	g_global->var = var;
	g_global->o_ac = ac;
	g_global->o_av = av;
	g_global->fds = NULL;
	g_global->cursor = cursor;
	if (ac > 1)
	{
		g_global->is_scrpt = 1;
		if ((g_global->f_fd = open(g_global->o_av[1], O_RDONLY, S_IRGRP
		| S_IRUSR)) < 0 || access(g_global->o_av[1], X_OK))
		{
			ft_putendl_fd("mysh: script: Permission denied", 2);
			exit(1);
		}
		else
			file_to_eval(var);
		exit_term(var);
	}
}
