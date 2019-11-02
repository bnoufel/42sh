/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:09:18 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:09:18 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int					check_done(char **line, int rec, t_par *par, long pos)
{
	int				j;
	int				do_flag;
	t_script_numb	numb;

	numb.numb = pos;
	do_flag = 0;
	j = 0;
	while ((*line)[numb.numbers.pos])
	{
		if ((j = check_done_2(line, rec, par, &numb.numb)) <= 0)
			return (j);
		else if (is_key(*line, "do", 0, numb.numbers.pos) == 1)
		{
			if (do_flag == 1)
				return (-2);
			if ((do_flag = 1) && numb.numbers.flag == 1 && rec == 0)
				return (numb.numbers.pos);
		}
		else if (numb.numbers.flag != 1 && is_key(*line, "done",
					0, numb.numbers.pos) == 1)
			return (numb.numbers.flag != 2 && !do_flag ? -1 : numb.numbers.pos);
		numb.numbers.pos++;
	}
	return (0);
}

int					check_while_token(char **line, int ground,
					int *end, t_par *par)
{
	int				i;
	int				test;
	t_script_numb	numb;

	numb.numb = 0;
	if ((i = find_key_pos(line, "while", *end, par)) == -1)
		return (g_global->sig ? -1 : 1);
	numb.numbers.pos = i;
	if ((test = check_done(line, 0, par, numb.numb)) <= 0)
	{
		if (test == -1)
		{
			g_global->sig ? 0 :
				ft_putstr_fd("\nError near done : missing 'do' keyword\n", 2);
			return (-1);
		}
		else if (test == -2)
			return (-1);
		if (read_script(line) == -1)
			return (-1);
		return (check_while_token(line, ground, end, par));
	}
	*end = test + 4;
	return (0);
}

int					get_while_cond(t_script **var, char *line, int i, int k)
{
	t_script		*tmp;
	t_script_numb	numb;

	if (!(numb.numb = 0) && !line)
		return (-1);
	tmp = *var;
	if ((i = find_key_pos(&line, "while", i, NULL)) != -1)
	{
		numb.numbers.pos = i;
		numb.numbers.flag = 1;
		k = check_done(&line, 0, NULL, numb.numb);
		tmp->cond = secured_malloc(line + i, 0, k - i, "get_while_cond");
		i = k + 2;
	}
	else
		return (-1);
	numb.numbers.pos = i;
	numb.numbers.flag = 2;
	k = check_done(&line, 0, NULL, numb.numb);
	tmp->body = secured_malloc(line + i, 0, k - i, "get_while_cond");
	return (0);
}

void				while_clause(t_script **var, t_var **env)
{
	t_script	*tmp;
	char		*cond;
	char		*body;
	int			c;
	int			t;

	c = 0;
	tmp = *var;
	c = 0;
	cond = secured_malloc(tmp->cond, -1, -1, "while_clause");
	while (!g_global->sig && !(tmp->r = eval(&cond, env)))
	{
		c = 1;
		body = secured_malloc(tmp->body, -1, -1, "while_clause");
		t = eval(&body, env);
		cond = secured_malloc(tmp->cond, -1, -1, "while_clause");
	}
	!c || (c && tmp->r && !t) ? (g_global->ret = 0) : 0;
	g_global->sig ? ft_strdel(&cond) : 0;
	ft_strdel(&tmp->cond);
	ft_strdel(&tmp->body);
}

int					while_tokenizer(t_var **env, char **line)
{
	t_script	*script;

	substitution(line);
	if (!(script = (t_script *)malloc(sizeof(t_script))))
		malloc_failed("while_tokenizer");
	script->body = NULL;
	script->cond = NULL;
	script->if_list = NULL;
	get_while_cond(&script, *line, 0, 0);
	while_clause(&script, env);
	free(script);
	script = NULL;
	return (0);
}
