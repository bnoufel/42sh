/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:08:54 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:08:55 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		check_for_token(char **line, int ground, int *end, t_par *par)
{
	int				test;
	t_script_numb	numb;

	numb.numb = 0;
	test = in_key_value(*line + *end);
	if (check_for_token_2(line, end, test, par) == -1)
		return (-1);
	numb.numbers.pos = test + *end;
	if ((test = check_done(line, 0, par, numb.numb)) <= 0)
	{
		if (test == -1 || test == -2)
		{
			test == -1 ?
			ft_putstr_fd("Error near done : missing 'do' keyword", 2) :
			ft_putstr_fd("Parsing Error", 2);
			return (-1);
		}
		if (read_script(line) == -1)
			return (-1);
		return (check_for_token(line, ground, end, par));
	}
	*end = test + 4;
	return (0);
}

int		for_tokenizer(t_var **env, char **line)
{
	t_script	*script;

	substitution(line);
	if (!(script = (t_script *)malloc(sizeof(t_script))))
		malloc_failed("for_tokenizer");
	script->body = NULL;
	script->cond = NULL;
	script->if_list = NULL;
	get_for_cond(&script, *line);
	g_global->ret = 0;
	for_clause(&script, env);
	free(script);
	script = NULL;
	return (0);
}

char	*set_for_var(char *var, char *value)
{
	char	*str;
	int		len;
	int		i;
	int		k;

	len = ft_strlen(var) + ft_strlen(value) + 3;
	k = -1;
	i = -1;
	if (!(str = (char *)malloc(len * sizeof(char))))
		malloc_failed("set_for_var");
	while (var && var[++k])
	{
		if (var[k] != ' ')
			str[++i] = var[k];
	}
	k = -1;
	str[++i] = '=';
	while (value && value[++k])
	{
		if (value[k] != ' ' && value[k] != ';')
			str[++i] = value[k];
	}
	str[++i] = '\0';
	return (str);
}

void	for_clause(t_script **var, t_var **env)
{
	t_script	*tmp;
	char		*cond;
	char		*body;
	char		**arr;
	int			i;

	tmp = *var;
	i = 0;
	arr = helpforclause(tmp->for_cond, env);
	while (arr && arr[i])
	{
		cond = set_for_var(tmp->for_var, arr[i]);
		ft_strlen(cond) < PATH_MAX
		? ft_list_nchange_if(env, cond, &env_strequ, 0) : 0;
		ft_strdel(&cond);
		body = secured_malloc(tmp->body, -1, -1, "for_clause");
		g_global->ret = eval(&body, env);
		i++;
	}
	ft_free_tab(arr);
	ft_strdel(&tmp->for_var);
	ft_strdel(&tmp->body);
	ft_strdel(&tmp->for_cond);
}

int		get_for_cond(t_script **var, char *line)
{
	t_script		*tmp;
	int				pos;
	int				i;
	t_script_numb	numb;

	i = 0;
	pos = 0;
	numb.numb = 0;
	if (!line)
		return (-1);
	tmp = *var;
	i = find_key_pos(&line, "for", i, NULL);
	tmp->for_var = secured_malloc(line + i, 0,
	find_key_pos(&line, "in", i, NULL) - i - 2, "get_for_cond");
	i = find_key_pos(&line, "in", i, NULL);
	pos = in_key_value(line);
	tmp->for_cond = secured_malloc(line + i, 0, pos - i, "get_for_cond");
	numb.numbers.pos = pos;
	numb.numbers.flag = 1;
	i = check_done(&line, 0, NULL, numb.numb) + 2;
	numb.numbers.pos = i;
	numb.numbers.flag = 2;
	pos = check_done(&line, 0, NULL, numb.numb);
	tmp->body = secured_malloc(line + i, 0, pos - i, "get_for_cond");
	return (0);
}
