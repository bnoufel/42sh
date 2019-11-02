/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avdelim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:39:12 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 15:39:13 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static	int			brret(char *s, char c, int i, t_par *cur)
{
	static int	a;

	if (cur && cur->br == 2 && s[i] == 41 && c == 41)
		a = i;
	else if (cur && ((cur->br == 1 && s[i] == 41 && c == 41 && i != a + 1)
				|| cur->br > 2))
		a = 0;
	if (s[i] == c)
	{
		if (cur && cur->math && a && cur->br == 1)
			cur->math = 1;
		else if (cur && cur->br == 1)
			cur->math = 0;
		c == 41 && cur ? cur->br-- : 0;
		cur ? cur->sub = 1 : 0;
		return (i);
	}
	cur ? ft_strncpy(cur->action, s + i, 1) : 0;
	return (0);
}

int					brackets(char **s, int i, t_par *cur, int r)
{
	int		a;
	char	c;

	a = i;
	c = wdelim(*s, &i, cur);
	if (r > 1000)
	{
		ft_putendl_fd("mysh : too many recursions", 2);
		ft_bye_bye(g_global->var, 0, NULL, 1);
	}
	while (*s && (*s)[i])
	{
		if (c && (((*s)[i] == 34 || (*s)[i] == '`') && !nbcks(*s, i - 1))
		&& !(i = skipquotes(s, i, cur, r + 1)))
			return (0);
		if ((*s)[i] == c && !nbcks(*s, i - 1))
			return (brret(*s, c, i, cur));
		else if (((*s)[i] == 40 || (*s)[i] == 123) && (!i || !nbcks(*s, i))
		&& (!(i = brackets(s, i, cur, r + 1))))
			return (0);
		i++;
	}
	if (!(outofrec(s, &i, c, cur)))
		return (0);
	return (i = i ? brackets(s, a, cur, r + 1) : 0);
}

int					skipquotes(char **s, int i, t_par *cur, int r)
{
	char	c;
	int		a;

	a = i;
	if (r > 1000)
	{
		ft_putendl_fd("mysh : too many recursions", 2);
		ft_bye_bye(g_global->var, 0, NULL, 1);
	}
	c = wdelim(*s, &i, cur);
	while (*s && (*s)[i] && ((*s)[i] != c || nbcks(*s, i - 1)))
	{
		if (c == 34 && (*s)[i] == 96 && !nbcks(*s, i - 1)
		&& !(i = skipquotes(s, i, cur, r + 1)))
			return (0);
		i++;
	}
	if ((*s)[i] == c)
		return (i);
	else if (!(outofrec(s, &i, c, cur)))
		return (0);
	return (i ? skipquotes(s, a, cur, r + 1) : 0);
}

static	int			equ(char *s, t_par *par, int *brk, int i)
{
	if (ft_strequ(s + i, ">&") || ft_strequ(s + i, "<&")
			|| ft_strequ(s + i, ">>") || ft_strequ(s + i, "<<")
			|| ft_strequ(s + i, "&&") || ft_strequ(s + i, "||"))
	{
		ft_strequ(s + i, "<&") ? ft_strcpy(par->action, "<&") : 0;
		ft_strequ(s + i, ">&") ? ft_strcpy(par->action, ">&") : 0;
		ft_strequ(s + i, "||") ? ft_strcpy(par->action, "||") : 0;
		ft_strequ(s + i, ">>") ? ft_strcpy(par->action, ">>") : 0;
		ft_strequ(s + i, "<<") ? ft_strcpy(par->action, "<<") : 0;
		ft_strequ(s + i, "&&") ? ft_strcpy(par->action, "&&") : 0;
		*brk = 1;
		return (1);
	}
	return (0);
}

int					avdelim(char **s, t_par **par, int *brk, int st)
{
	int		i;
	int		t;

	i = st - 1;
	t = 0;
	while ((*s) && (*s)[++i])
	{
		isbkslsh(s, &i);
		if (*s && !g_global->par && (*s)[i] == 41 && ((*par)->action[0] = ')'))
			break ;
		if (!(*s) || (!g_global->par && ((((*s)[i] == 34 || (*s)[i] == 39
		|| (*s)[i] == 96) && !(i = skipquotes(s, i, *par, 0)))
		|| (((*s)[i] == 40 || (*s)[i] == 123) && !helpbrackets2(s, &i, *par)))))
			break ;
		if (*s && !g_global->par && ((!(t = check_script_tokenizer(s, &i, 0,
		*par)) && (*brk = 1)) || equ(*s, *par, brk, i)))
			return (i);
		else if (t == -1 && ((*par)->action[0] = 'K'))
			break ;
		if (*s && ((!g_global->par && digit(brk, (*s) + i, *par))
		|| onec(brk, (*s) + i, *par)))
			return (i);
	}
	return (((*par)->action[0] == ')'
	|| (*par)->action[0] == 'K') && !((*par)->action[1] = '\0') ? i : -1);
}
