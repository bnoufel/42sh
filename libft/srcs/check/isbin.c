/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:09:02 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:10:43 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		isbin(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] < 0 || s[i] > 126)
			return (1);
		i++;
	}
	return (0);
}