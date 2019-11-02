/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:09:14 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:09:15 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		check_quotes(char **haystack, int *i, t_par *par)
{
	if (((*haystack)[*i] == 34 || (*haystack)[*i] == 39
		|| (*haystack)[*i] == 96) && !(*i = skipquotes(haystack, *i, par, 0)))
		return (1);
	if ((*haystack)[*i] == 40 && !helpbrackets2(haystack, i, par))
		return (1);
	return (0);
}

int		find_key_pos(char **haystack, const char *needle, int i,
		t_par *par)
{
	int b;
	int c;

	c = 0;
	while (*haystack && (*haystack)[i])
	{
		b = 0;
		if (c)
			i = c + 1;
		if (check_quotes(haystack, &i, par) == 1)
			break ;
		while ((*haystack)[i] && (*haystack)[i] != needle[b])
			i++;
		c = i;
		while ((*haystack)[i] && (*haystack)[i] == needle[b])
		{
			i++;
			b++;
		}
		if (!needle[b] && (!(*haystack)[i] || (*haystack)[i] == ' '
					|| (*haystack)[i] == ';' || (ft_isdigit((*haystack)[i])
						&& !ft_strcmp(needle, "$"))))
			return (i);
	}
	return (-1);
}

int		str_to_gnl(char **str, int fd)
{
	char	*gnl_str;
	int		read_state;
	int		end;

	end = 0;
	read_state = gnl(fd, &gnl_str, 1);
	if (read_state <= 0)
	{
		ft_putendl_fd("Unexpected End of File", 2);
		ft_bye_bye(g_global->var, 0, NULL, 1);
	}
	if (skip_comment(&gnl_str) == 2)
		return (str_to_gnl(str, fd));
	if (!(*str = ft_strjoinfree(*str, ft_strjoinfree(";", gnl_str, 2), 3)))
		malloc_failed("str_to_gnl");
	return (0);
}

int		script_tokenizer(t_var **env, t_par **cur, int i)
{
	while ((*cur) && !(*cur)->lav && !(*cur)->action[0])
	{
		if ((*cur)->next)
			(*cur) = (*cur)->next;
		else
			return (0);
	}
	if ((*cur) && !(*cur)->lav && (*cur)->action[0])
		return (1);
	if (((*cur)->sub && (*cur)->lav && (*cur)->lav->av[0] == 40)
	|| (!(*cur)->lav && ((*cur)->action[0] == '<'
	|| (*cur)->action[0] == '>')))
		return (1);
	while ((*cur)->lav->av[i])
	{
		if (is_key((*cur)->lav->av, "while", 1, i) == 1)
			return (while_tokenizer(env, &((*cur)->lav->av)));
		if (is_key((*cur)->lav->av, "if", 3, i) == 1)
			return (if_tokenizer(env, &((*cur)->lav->av)));
		if (is_key((*cur)->lav->av, "for", 2, i) != 0)
			return (for_tokenizer(env, &((*cur)->lav->av)));
		i++;
	}
	return (1);
}
