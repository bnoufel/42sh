/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equalizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:04:18 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:04:19 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __EQUALIZER_H
# define __EQUALIZER_H

typedef struct			s_cmp
{
	char				*start;
	char				*end;
	char				*str;
	char				*cmp;
	char				*str1;
	int					isnot;
	int					error;
	bool				str_is_integer;
	bool				str1_is_integer;
}						t_cmp;

void					the_equalizer_error(t_cmp *cmp);

/*
** Check arg
*/

int						init_struct_with_no_valid_cmp(t_cmp *cmp, char **str);
int						init_struct_with_valid_cmp(t_cmp *cmp, char **str);
int						valid_cmp_before(char *str);
int						init_struct(char **str, t_cmp *cmp);

/*
** Check files
*/

bool					check_if_is_a_spec_file(t_cmp *cmp);
bool					check_if_file_no_empty(t_cmp *cmp);
bool					check_file_exist(t_cmp *cmp);
bool					check_file_right(t_cmp *cmp);
bool					check_modification_file(t_cmp *cmp);

/*
** Check int string
*/

bool					check_string_if_empty_null(t_cmp *cmp);
bool					check_equalizer_int(t_cmp *cmp);

/*
** CORE
*/

void					equalizer_free(t_cmp *cmp);
void					ft_compare(t_par *cur, int *r);
int						check_struct(t_cmp *cmp);
char					**equalizer_core(t_par *cur);
bool					the_equalizer(t_cmp *cmp);
#endif
