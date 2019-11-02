/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while_tokenizer_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:09:19 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:09:23 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			check_done_3(char **line, int rec, int *i, t_par *par)
{
	int j;

	j = 0;
	if (is_key(*line, "if", 1, *i) == 1)
	{
		j = make_if_great_again(line, rec + 1, *i + 1, par);
		if (j < -1)
			return (j);
		if (j == -1)
			return (0);
		*i = j + 2;
	}
	return (1);
}

int			check_done_2(char **line, int rec,
		t_par *par, long *pos)
{
	int				j;
	t_script_numb	numb;
	int				save_flag;

	numb.numb = *pos;
	save_flag = numb.numbers.flag;
	numb.numbers.flag = 0;
	j = 0;
	if (check_quotes(line, &numb.numbers.pos, par) == 1)
		return (-2);
	if (is_key(*line, "while", 1, numb.numbers.pos) == 1
			|| is_key(*line, "for", 2, numb.numbers.pos) == 1)
	{
		j = check_done(line, rec + 1, par, numb.numb + 1);
		if (j <= 0)
			return (j);
		numb.numbers.pos = j + 2;
	}
	if ((j = check_done_3(line, rec, &numb.numbers.pos, par)) <= 0)
		return (j);
	numb.numbers.flag = save_flag;
	*pos = numb.numb;
	return (1);
}
