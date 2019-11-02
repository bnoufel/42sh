/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:04:52 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:04:56 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int			ft_find_rank(t_list *list)
{
	int				i;

	i = 0;
	while (list->prev)
	{
		i++;
		list = list->prev;
	}
	return ((i == 0) ? i : i - 1);
}

static void			ft_change_name(t_auto *lst, mode_t mode)
{
	if (!(lst->color = ft_strdup(ft_ac_color(mode))))
		malloc_failed("ft_set_color");
	if (S_ISDIR(mode))
	{
		if (!(lst->after = ft_strdup("/")))
			malloc_failed("ft_set_color");
	}
	else if (S_ISLNK(mode))
	{
		if (!(lst->after = ft_strdup("@")))
			malloc_failed("ft_set_color");
	}
	else if (mode & S_IXOTH || mode & S_IXUSR || mode & S_IXGRP)
	{
		if (!(lst->after = ft_strdup("*")))
			malloc_failed("ft_set_color");
	}
	else if (S_ISCHR(mode))
	{
		if (!(lst->after = ft_strdup("%")))
			malloc_failed("ft_set_color");
	}
	else if (!(lst->after = ft_strdup("\0")))
		malloc_failed("ft_set_color");
}

static void			ft_set_color(t_auto **head)
{
	t_auto			*lst;
	char			*tmp;
	t_stat			st;

	lst = *head;
	lst = lst->next;
	while (lst)
	{
		if (lst->head == 1)
			break ;
		if (lst->path[0] != '\0' && lst->path[ft_strlen(lst->path) - 1] != '/')
			if (!(lst->path = ft_strjoinfree(lst->path, "/", 1)))
				malloc_failed("ft_set_color");
		if (!(tmp = ft_strjoin(lst->path, lst->str)))
			malloc_failed("ft_set_color");
		if (lstat(ac_remove_backslash(tmp), &st) == -1)
		{
			lst = lst->next;
			free(tmp);
			continue ;
		}
		free(tmp);
		ft_change_name(lst, st.st_mode);
		lst = lst->next;
	}
}

static bool			ac_bind_auto_completion(t_list **list, t_cursor *cursor,
																t_var **var)
{
	int				rang;
	char			*str;
	t_auto			*head;
	t_split			*folder;

	rang = ft_find_rank(*list);
	str = ft_list_to_string(*list, 1);
	if (ft_add_slash(str, rang, list, cursor) == 1)
	{
		ft_return_to_rang(list, rang);
		free(str);
		return (false);
	}
	folder = ac_init_struct(str, rang);
	head = ac_get_occu(folder, ft_find_elem(str, rang), var);
	if (head)
	{
		ft_set_color(&head);
		ft_fill_line(head, str, var, rang);
		ac_free_auto(head);
	}
	ac_free_struct(folder);
	free(str);
	return (true);
}

void				ft_auto_completion(t_list **list, t_cursor *cursor,
																t_var **var)
{
	cursor->completion++;
	if ((*list)->c == '\\' && (*list)->next->c == ' ')
		left_down_right_up(" [C", list, cursor, *list);
	if ((*list)->next->c != ' ')
	{
		while ((*list)->next->c != ' ')
			left_down_right_up(" [C", list, cursor, *list);
		if ((*list)->c == '\\' && (*list)->next->c == ' ')
			left_down_right_up(" [C", list, cursor, *list);
		while ((*list)->next->c != ' ')
			left_down_right_up(" [C", list, cursor, *list);
		cursor->completion = 0;
		return ;
	}
	if (!(ac_bind_auto_completion(list, cursor, var)))
		return ;
}
