/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keatchut <keatchut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 10:10:43 by keatchut          #+#    #+#             */
/*   Updated: 2018/10/19 10:10:49 by keatchut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SCRIPT_H
# define __SCRIPT_H

typedef struct			s_if_list
{
	char				*if_cond;
	char				*then;
	int					else_flag;
	struct s_if_list	*next;
}						t_if_list;

typedef struct			s_script
{
	char				*cond;
	int					r;
	char				*body;
	char				*for_cond;
	char				*for_var;
	struct s_if_list	*if_list;
}						t_script;

typedef	union			u_script_numb
{
	long				numb;
	struct				s_numbers
	{
		int				pos;
		int				flag;
	}					numbers;
}						t_script_numb;

int						check_done(char **line, int rec, t_par *par, long pos);
int						check_done_2(char **line, int rec,
						t_par *par, long *pos);
int						check_for_token(char **line, int ground,
						int *end, t_par *par);
int						check_for_token_2(char **line, int *end,
						int test, t_par *par);
int						check_if(char **line, int ground, int *end, t_par *par);
int						check_quotes(char **haystack, int *i, t_par *par);
int						check_script_tokenizer(char **line, int *end,
						int ground, t_par *par);
int						check_while_token(char **line, int ground,
						int *end, t_par *par);
int						filllav(t_av **keep, t_par **t, t_par **cu, t_av **tm);
int						find_key_pos(char **haystack,
						const char *needle, int i, t_par *par);
void					for_clause(t_script **var, t_var **env);
int						for_tokenizer(t_var **env, char **line);
void					free_if_list(t_if_list **list, int flag);
int						get_for_cond(t_script **var, char *line);
int						hashkey(t_par **cur, char **gs);
char					**helpforclause(char *s, t_var **var);
void					if_clause(t_script **var, t_var **env);
int						in_key_value(char *line);
int						is_for(char *line, int pos);
int						if_tokenizer(t_var **env, char **line);
int						is_key(char *line, char *key, int flag, int pos);
int						make_else_great_again(char **line, int i, t_par *par);
int						make_if_great_again(char **line, int rec,
						int i, t_par *par);
int						noshellbang(t_par **cur, t_par **topar, int i);
int						read_script(char **line);
char					*secured_malloc(char *str, int start,
						int end, char *error);
int						script_tokenizer(t_var **env, t_par **cur, int i);
int						skip_comment(char **line);
int						str_to_gnl(char **str, int fd);
int						substitution(char **line);
int						while_tokenizer(t_var **env, char **line);
int						get_cond(t_script **var, char *line);
#endif
