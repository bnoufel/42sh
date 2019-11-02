/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:09:03 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:09:04 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			pos_to_next_key(char *line)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (line[i])
	{
		if (((line)[i] == 34 || (line)[i] == 39 || (line)[i] == 96)
				&& !(i = skipquotes(&line, i, NULL, 0)))
			break ;
		if (is_key(line, "if", 3, i) == 1)
		{
			j = make_if_great_again(&line, 0, i + 1, NULL);
			if (j <= 0)
				return (-1);
			i = j + 2;
		}
		if (is_key(line, "elif", 1, i) == 1
				|| is_key(line, "else", 1, i) == 1
				|| is_key(line, "then", 1, i) == 1
				|| is_key(line, "fi", 1, i) == 1)
			return (i);
		line[i] ? i++ : 0;
	}
	return (0);
}

int			cut_to_key(char *line, int k, t_if_list **list, int flag)
{
	int			i;
	t_if_list	*tmp;

	tmp = *list;
	i = 0;
	if (flag == 1)
	{
		tmp->else_flag = 1;
		tmp->then = secured_malloc(line, 0, k, "cut_to_key");
		return (k);
	}
	tmp->if_cond = secured_malloc(line, 0, k, "cut_to_key");
	i = k + 4;
	if ((k = pos_to_next_key(line + i)) < 0)
		return (0);
	tmp->then = secured_malloc(line + i, 0, k, "cut_to_key");
	return (k + i);
}

t_if_list	*malloc_if_list(void)
{
	t_if_list	*tmp;

	if (!(tmp = (t_if_list *)malloc(sizeof(struct s_if_list))))
		malloc_failed("malloc_if_list");
	tmp->if_cond = NULL;
	tmp->else_flag = 0;
	tmp->then = NULL;
	tmp->next = NULL;
	return (tmp);
}

void		get_cond_2(t_if_list **var, char *line, int i, int k)
{
	while (line[i + k] && k > 0)
	{
		i += k;
		if ((k = pos_to_next_key(line + i + 1)) <= 0)
			break ;
		(*var)->next = malloc_if_list();
		(*var) = (*var)->next;
		if (is_key(line, "elif", 1, i) == 1)
			k = cut_to_key(line + i + 4, k - 3, var, 0) + 4;
		else if (is_key(line, "else", 1, i) == 1)
			k = cut_to_key(line + i + 4, k - 3, var, 1) + 4;
	}
}

int			get_cond(t_script **var, char *line)
{
	int			k;
	t_script	*script;
	t_if_list	*tmp;
	int			i;

	script = *var;
	if (!script->if_list)
		script->if_list = malloc_if_list();
	tmp = script->if_list;
	i = 0;
	if ((i = find_key_pos(&line, "if", i, NULL)) == 0)
		return (0);
	if ((k = pos_to_next_key(line + i)) < 0)
		return (0);
	tmp->if_cond = secured_malloc(line + i, 0, k, "get_cond");
	i += k + 4;
	if ((k = pos_to_next_key(line + i)) <= 0)
		return (0);
	tmp->then = secured_malloc(line + i, 0, k, "get_cond");
	get_cond_2(&tmp, line, i, k);
	return (0);
}
