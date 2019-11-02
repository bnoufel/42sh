/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:05:32 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:05:34 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char		*ft_realloc_new(char *original, char *compl, int rang)
{
	char		*new;
	int			i;
	int			a;
	int			save;

	a = -1;
	i = rang;
	if (!original || !compl)
		return (NULL);
	if (!(new = (char *)malloc(sizeof(char) * (ft_strlen(original)
		+ ft_strlen(compl) + 1))))
		malloc_failed("ft_realloc_new");
	while (i > 0 && ((original[i - 1] == ' ' && original[i - 2] == '\\')
	|| (original[i - 1] != ' ' && original[i - 1] != '/')))
		i--;
	save = rang + 1;
	while (++a < i)
		new[a] = original[a];
	a = 0;
	while (compl[a])
		new[i++] = compl[a++];
	while (original[save])
		new[i++] = original[save++];
	new[i] = '\0';
	return (new);
}

static char		*ft_realloc_without_ending_space(char *str)
{
	char		*new;
	int			i;

	i = 0;
	if (!(new = (char *)malloc(sizeof(char) * ft_strlen(str))))
		malloc_failed("ft_realloc_without_ending_space");
	while (str[i + 1])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static void		ft_multiple(t_auto *head, int number, t_var **var)
{
	count_and_erase_line((*g_global->cursor), g_global->first, 3);
	ft_info_line((*g_global->cursor), var);
	ft_read_list(g_global->first, (*g_global->cursor), 0);
	ft_display_compl(head, number);
}

void			ft_return_to_rang(t_list **list, int rang)
{
	int i;

	i = -1;
	(*list)->next->state = 0;
	while ((*list)->prev)
		*list = (*list)->prev;
	while ((*list)->next->next && i++ < rang)
		left_down_right_up(" [C", list, (*g_global->cursor), g_global->first);
	while ((*list)->next->next && ((*list)->next->c != ' '
	|| ((*list)->next->c == ' ' && (*list)->c == '\\')))
		left_down_right_up(" [C", list, (*g_global->cursor), g_global->first);
}

void			ft_fill_line(t_auto *head, char *str, t_var **var, int rang)
{
	char		*new;
	int			number;

	head = head->next;
	number = ft_autolen(head);
	if (number == 0)
		(*g_global->cursor)->completion = 0;
	else if (number == 1)
	{
		if (str[rang] == '/' || str[rang] == ' ')
			new = ft_realloc_new_bis(ft_realloc_without_ending_space(str),
													head->str, rang + 1);
		else
			new = ft_realloc_new(str, head->str, rang);
		ft_str_to_list(new, g_global->list);
		(*g_global->cursor)->completion = 0;
		free(new);
		ft_return_to_rang(g_global->list, rang);
	}
	else
		ft_multiple(head, number, var);
}
