/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:04:33 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:10:02 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char			*ft_realloc_new_bis(char *tmp, char *str, int rang)
{
	int		i;
	int		a;
	char	*new;

	if (!(new = (char *)malloc(sizeof(char) * (ft_strlen(tmp)
		+ ft_strlen(str) + 2))))
		malloc_failed("realloc_new_bis");
	a = -1;
	i = -1;
	while (++i < rang)
		new[i] = tmp[i];
	while (++a < (int)ft_strlen(str))
		new[i + a] = str[a];
	while (tmp[rang])
	{
		new[i + a] = tmp[rang];
		i++;
		rang++;
	}
	new[i + a] = ' ';
	new[i + a + 1] = '\0';
	free(tmp);
	return (new);
}
