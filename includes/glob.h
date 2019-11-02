/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:10:33 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:10:53 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __GLOB_H
# define __GLOB_H

typedef struct dirent	t_dirent;
typedef struct			s_split
{
	char				*before;
	char				*middle;
	char				*after;
}						t_split;
typedef struct			s_braces
{
	char				**str;
	int					is_good;
	int					is_num;
}						t_braces;
typedef struct			s_star
{
	struct s_star		*right;
	struct s_star		*left;
	char				*entry;
	int					mode;
}						t_star;
/*
** @brief List/Tab for globing
*/
bool					ft_free_tab(char **to_free);
void					free_struct_folder(t_split *split);
bool					split_folder_hook(t_split *split, char *str, int ec[3]);
bool					split_folder_braces(t_split *split, char *str,
						char ***core);
bool					split_folder_star(t_split *split, char *str);
/*
** @brief Parser
*/
char					*hook_parser(char **str, int *j, t_var *var);
char					*braces_parser(char **str, int *j);
char					*star_parser(char **str, int *j);
/*
** @brief Checker
*/
int						initstarquery(DIR **odir, char **open, t_split *split);
bool					number_braces_valid(char *str);
bool					check_hook_file_exist(char *str);
bool					check_max(long min, long max, long *diff);
bool					check_is_valid_number(char *min, char *max);
/*
** @brief Bind data
*/
t_star					*create_node(t_dirent *rdir);
void					insert_data(t_star **root, t_dirent *rdir);
char					*transform_tab_to_char(char **temp);
char					*braces_cat_letter(t_split *split, char **core);
char					*braces_cat_number(t_split *split, char **core);
void					braces_bind_number(char **ret, int min, int max,
						t_split *spl);
int						diff_min_max(int min, int max);
char					*braces_bind(t_split *split, t_braces *braces,
						int *recu);
/*
** @brief Core
*/
char					*glob_core_while(char *str, int *j, t_var *var, int c);
int						match(char *s1, char *s2);
char					*get_open_dir(char *str);
#endif
