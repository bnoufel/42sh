/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_tokenizer_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:09:05 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:09:06 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		check_correct_if_2(char **line, int i, int *then_flag, t_par *par)
{
	int j;

	j = 0;
	if (is_key(*line, "elif", 1, i) == 1
	|| (j = is_key(*line, "fi", 0, i) + 1) == 2
	|| (j = is_key(*line, "else", 1, i) + 2) == 3)
	{
		if (*then_flag == 0)
			return (-2);
		if (j == 2)
			return (i);
		if (j == 3)
			return (make_else_great_again(line, i + 1, par));
		*then_flag = 0;
	}
	if (is_key(*line, "then", 1, i) == 1)
	{
		if (*then_flag == 1)
			return (-2);
		*then_flag = 1;
	}
	return (0);
}

int		make_if_great_again(char **line, int rec, int i, t_par *par)
{
	int j;
	int then_flag;
	int r;

	j = 0;
	then_flag = 0;
	r = 0;
	while ((*line)[i])
	{
		if ((((*line)[i] == 34 || (*line)[i] == 39 || (*line)[i] == 96)
				&& !(i = skipquotes(line, i, par, 0))) || ((*line)[i] == 40
				&& !helpbrackets2(line, &i, par)))
			return (-2);
		if (is_key(*line, "if", 3, i) == 1)
		{
			j = make_if_great_again(line, rec + 1, i + 1, par);
			if (j <= -1)
				return (j);
			i = j + 2;
		}
		if ((r = check_correct_if_2(line, i, &then_flag, par)) != 0)
			return (r);
		i++;
	}
	return (-1);
}

int		check_if(char **line, int ground, int *end, t_par *par)
{
	int test;
	int	i;

	i = *end;
	if ((i = find_key_pos(line, "if", i, par)) == -1)
		return (g_global->sig ? -1 : 1);
	if ((test = make_if_great_again(line, 0, i, par)) <= -1)
	{
		if (test == -2)
		{
			ft_putstr_fd("\nParsing error\n", 2);
			return (-1);
		}
		if (read_script(line) == -1)
			return (-1);
		return (g_global->sig ? -1 : check_if(line, ground, end, par));
	}
	*end = test + 2;
	return (0);
}

void	if_clause(t_script **var, t_var **env)
{
	t_if_list	*tmp2;
	t_script	*tmp;
	t_if_list	*to_free;

	tmp = *var;
	tmp2 = (*var)->if_list;
	while (tmp2)
	{
		if (tmp2->else_flag == 1 || !(tmp->r = eval(&(tmp2->if_cond), env)))
		{
			g_global->ret = eval(&(tmp2->then), env);
			to_free = tmp2;
			free_if_list(&tmp2->next, 1);
			free(to_free);
			to_free = NULL;
			break ;
		}
		else
		{
			g_global->ret = 0;
			to_free = tmp2;
			tmp2 = tmp2->next;
			free_if_list(&to_free, 0);
		}
	}
}

int		if_tokenizer(t_var **env, char **line)
{
	t_script	*script;

	script = NULL;
	substitution(line);
	if (!(script = (t_script *)malloc(sizeof(t_script))))
		malloc_failed("if_tokenizer");
	script->body = NULL;
	script->cond = NULL;
	script->if_list = NULL;
	get_cond(&script, *line);
	if_clause(&script, env);
	free(script);
	script = NULL;
	return (0);
}
