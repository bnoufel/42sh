/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myterm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:03:49 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:03:50 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MYTERM_H
# define __MYTERM_H
# ifndef __GLOB_H
#  include "glob.h"
# endif
# ifndef __MINISHELL_H
#  include "minishell.h"
# endif
# ifndef __HASH_H
#  include "hash.h"
# endif

# include <dirent.h>
# include <limits.h>

typedef struct			s_list
{
	int					state;
	int					selected;
	char				c;
	int					erase;
	int					qdbs;
	struct s_list		*next;
	struct s_list		*prev;
}						t_list;

typedef struct			s_history
{
	struct s_list		*list;
	struct s_history	*next;
	struct s_history	*prev;
	int					head;
	int					file;
}						t_history;

typedef struct			s_cursor
{
	int					col;
	struct winsize		window;
	int					color;
	t_list				*save;
	t_history			*history;
	int					is_selected;
	int					fd;
	int					add_line;
	struct termios		*old;
	int					search;
	int					a;
	int					completion;
	int					res_search;
	int					job;
	char				*path;
}						t_cursor;

typedef struct			s_parno
{
	t_list				*copy;
	t_list				*head;
	t_list				*tmp;
	t_list				*tmp2;
}						t_parno;

typedef struct			s_auto
{
	char				*str;
	char				*path;
	char				*after;
	int					head;
	int					selected;
	int					size;
	char				*color;
	struct s_auto		*next;
	struct s_auto		*prev;
}						t_auto;

typedef struct			s_pid
{
	pid_t				pid;
	struct s_pid		*next;
}						t_pid;

typedef struct			s_global
{
	t_list				**list;
	t_cursor			**cursor;
	t_list				*first;
	int					sig;
	int					sub;
	int					par;
	t_pid				*pid;
	t_pid				*ck;
	int					ret;
	t_var				**var;
	int					prefix;
	bool				jobs;
	bool				control;
	char				*cmdline;
	int					sear;
	int					pipe;
	t_hash				**buckets;
	t_bin				*bin;
	t_dir				*spwd;
	int					fdmax;
	int					bg;
	int					o_ac;
	char				**o_av;
	int					f_fd;
	int					is_scrpt;
	int					stdi;
	int					env;
	t_fds				*fds;
}						t_global;

t_global				*g_global;

/*
** LIST
*/

void					ft_init_list(t_list **list);
void					ft_add_elem(t_list **list, char c, t_list *next);
void					ft_read_list(t_list *first, t_cursor *cursor, int a);
void					ft_free_all(t_list **list);
void					ft_free_right_node(t_list **list);
void					ft_free_left_node(t_list **list);
char					*ft_list_to_string(t_list *list, int n);
void					ft_list_auto(t_auto **list, char *str, char *to_open);
void					ft_head_auto(t_auto **list);
int						ft_autolen(t_auto *list);
void					ft_add_auto(t_auto **list, char *str, char *to_open);
void					ac_free_auto(t_auto *head);
void					ac_free_struct(t_split *folder);

/*
** TERM
*/

void					exit_term(t_var **var);
void					ft_ioctl(t_cursor *cursor);
char					*ft_putstr_special(char *str, char c);
char					*ft_return_home(char *str);
void					count_and_erase_line(t_cursor *cursor, t_list *first,
						int nb);
int						left_down_right_up(char *buff, t_list **list,
						t_cursor *cursor, t_list *first);
void					ft_add_cursor(t_cursor *cursor, t_list *first,
						t_list **list, t_var **var);
void					init_cursor(t_cursor *cursor, int n);
int						ft_is_what_i_want(char *buff, t_list **list,
						t_cursor *cursor, t_var **var);
int						ft_home_end(t_list **list, char *buff);
void					init_term(t_cursor *cursor, int n, t_var **var,
						int job);
void					ft_enter(t_list **list, t_cursor *cursor, t_list *first,
						t_var **v);
void					ft_right_word(t_list **l, char *buff, t_cursor *c,
						t_list *first);
void					ft_left_word(t_list **list, char *buff, t_cursor *c,
						t_list *first);
int						gnl(int fd, char **line, int cut);
int						term1(int *shell_pgid, int *shell_is_interactive,
						int *o_pgid);
int						term2(t_var **var);
int						ft_is_emptyline(t_list *l);
void					ft_add_realloc(char **cmd, char c, int pos);
int						ft_mini_loop(int *i, int *pos, char **cmd, char *buff);

/*
** Free
*/

void					ft_free_all_jobs(void);
int						ft_is_job_activ(void);
void					ft_free_pgid(void);
void					ft_free_cursor(t_var **var, char **buff);
void					ft_free_edition(void);
void					ft_free_cccv(void);
void					ft_free_histo(void);

/*
** Cut Copy paste
*/

void					ft_copy_cut(t_cursor *cursor, t_list **list, int n,
						t_list *first);
void					ft_save_node(t_cursor *cursor, t_list **list, int n);
t_list					*ft_copy_node(t_list *list);
void					ft_select(t_list **list, t_cursor *cursor, int selector,
						t_list *first);
t_list					*ft_copy_linked_list(t_list *list, int *nb);
void					ft_reset_selection(t_list **list);
void					ft_paste(t_list **list, t_cursor *cursor,
						t_list *first);

/*
** HISTORY
*/

void					ft_open(t_cursor *cursor);
int						ft_up_down_history(t_cursor *c, char *s, t_list **l,
						t_list *f);
void					ft_research(t_cursor *c, t_list *f, t_list **l,
						char *b);
t_list					*ft_finda(t_cursor *c, t_list *f, char *b, t_list **l);
void					ft_prompt(t_cursor *c);
void					ft_hist_next(t_cursor *cursor, t_list *f, t_list *l);
void					ft_realloc_with_pos(char **str, char *place, int pos);
char					*ft_cut_str(char *str);
char					*whichone(char **tmp, char **str, int *i);
char					*whichtwo(char **tmp, char **str, int *i);
char					*whichthree(char **tmp, char **str, int *i,
						char **tmp2);
t_history				*ft_init_history(void);

/*
** OPTIONS + KEY
*/

void					ft_option(char *b, t_list **l, t_cursor *c, t_list *f);
void					ft_up_down(t_list **l, t_cursor *c, int n, t_list *f);

/*
** MISC
*/

void					ft_info_line(t_cursor *cursor, t_var **var);
int						ft_bye_bye(t_var **var, int n, char **buff, int r);
void					ft_close(t_cursor *cursor);
void					ft_count_line(t_cursor *cursor, t_list *list,
						int nb);
void					ft_realloc_term(char **str, char c);

/*
** Completion
*/

t_auto					*ac_readdir_bin(char *env, t_split *f, int i, int b);
char					*ac_open_folder(const char *s, int c);
bool					ac_match(const char *s1, const char *s2);
t_auto					*ac_read_path_bin(t_split *folder, int bin, char *old);
void					ft_auto_completion(t_list **l, t_cursor *c, t_var **v);
void					*ac_get_occu(t_split *folder, int bin, t_var **var);
t_split					*ac_init_struct(char *str, int index);
void					ac_read_builtin(t_auto **lst, t_split *folder);
char					*ft_getenv(char *search, t_var **var);
char					*ft_ac_color(mode_t mode);
void					ft_str_to_list(char *str, t_list **list);
int						ft_find_elem(char *str, int number);
void					ft_display_compl(t_auto *head, int number);
void					ft_fill_line(t_auto *head, char *s, t_var **v, int r);
int						ft_add_slash(char *s, int n, t_list **l, t_cursor *c);
char					*ac_remove_backslash(char *str);
char					*ac_add_backslash(char *str);

/*
** SIGNAL
*/

void					ft_plu(t_cursor *cursor, t_var **var);
void					sig_h(int n);
void					ft_open_sig(void);
void					ft_catch_sig(int n);
void					set_signal_main(void);

/*
** Misc
*/

int						ft_mini_read(char **cmd, int *i, int qdbs, char c);
void					ft_qdbs(t_cursor *c, t_list **l, t_list *f, int q);
void					ft_return_to_rang(t_list **list, int rang);
char					*ft_realloc_new_bis(char *tmp, char *str, int rang);
int						ft_cursorless();
int						ft_mini_want(char *buff, int *i, int *pos, char **cmd);
void					ft_delete_realloc(char **cmd, int pos);
int						left_right(t_list **list, char *buff, int *i);
int						ft_display_esc(void);
int						ft_count_search(t_list *list, int nb);
int						ft_check_before_2(char **str);
int						ft_read_list2(t_list *first, t_cursor *c);
int						ft_check_before_launch(char **str);
void					ft_choose_prompt(t_cursor *cursor, t_var *var,
						t_list *first);
void					prompt_git(char **prompt);

/*
** Builtin history
*/

void					ft_built_in_exc(char **str);
int						ft_find_r(int n);
char					*ft_find_in_history(int n, int other);
char					*ft_find_in_history2(char *to_find);
char					*list_to_char(t_list *list);
void					ft_delete_word(char **str, int i, int number);
int						ft_history();

/*
** Display unicode
*/

void					ft_display_arrow(int n);
void					ft_display_delete(int n);
void					ft_display_enter(void);
void					ft_display_tab(void);

/*
** Init
*/

t_var					*init_var(void);
void					init_g(t_var **var, int ac, char **av, t_cursor **c);

#endif
