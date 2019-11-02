/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_tokenizer_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:09:07 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:09:08 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		make_else_great_again(char **line, int i, t_par *par)
{
	int	j;

	j = 0;
	while ((*line)[i])
	{
		if (((*line)[i] == 34 || (*line)[i] == 39 || (*line)[i] == 96)
				&& !(i = skipquotes(line, i, par, 0)))
			break ;
		if ((*line)[i] == 40 && !helpbrackets2(line, &i, par))
			break ;
		if (is_key(*line, "elif", 1, i) == 1)
			return (-2);
		else if (is_key(*line, "else", 1, i) == 1)
			return (-2);
		else if (is_key(*line, "if", 3, i) == 1)
			return (-2);
		else if (is_key(*line, "fi", 0, i) == 1)
			return (i);
		i++;
	}
	return (-1);
}
