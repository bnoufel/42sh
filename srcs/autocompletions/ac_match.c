/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:04:27 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:04:32 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

bool			ac_match(const char *s1, const char *s2)
{
	size_t		i;

	i = 0;
	if (ft_strcmp(s1, s2) == 0)
		return (true);
	while (s1[i] == s2[i])
		i++;
	if (i == ft_strlen(s2))
		return (true);
	return (false);
}
