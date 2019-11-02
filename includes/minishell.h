/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:00:53 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 16:00:55 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>

typedef struct		s_env
{
	char			elem[LINE_MAX];
	struct s_env	*next;
}					t_env;

typedef struct		s_av
{
	struct s_av		*last;
	char			*av;
	struct s_av		*next;
	struct s_av		*prev;
	struct s_av		*head;
}					t_av;

typedef struct		s_par
{
	struct s_par	*next;
	struct s_par	*prev;
	char			action[13];
	struct s_par	*tofree;
	int				ac;
	t_av			*lav;
	char			**av;
	int				fd[2];
	int				bg;
	int				br;
	int				math;
	int				sub;
	int				q;
}					t_par;

typedef struct		s_var
{
	t_env			*lenv;
	t_env			*loc;
	t_env			*exp;
	t_env			*fnc;
	char			**tenv;
}					t_var;

typedef struct		s_dir
{
	char			old_pwd[PATH_MAX];
	char			pwd[PATH_MAX];
	int				s;
	int				l;
	int				p;
}					t_dir;

typedef struct		s_fds
{
	struct s_fds	*next;
	int				fd;
}					t_fds;

char				**adaptarray(t_var **var);
char				**recpyenv(t_var **var);
char				*afterop(char *s);
char				*bckslshav(char *s, char c);
char				*beforeop(char *s, int i);
char				*cdpath(char *paths, char *cmd);
t_env				*check_in_list(t_env **liste, t_env **prev,
					char *to_find, int *i);
t_av				*checkassign(t_par **cur, t_var *var);
t_av				*checkifvar(t_par *cur, t_var **var, int j, int f);
char				*cksubmath(char **s, t_var *var, t_par *par, int *l);
char				*cleans(char *s, char **s2);
char				*conversion(char **s, int a);
t_env				*copyenv(char **environ, t_var *var, int c, int d);
t_env				*create_elem(char *name);
char				*dupspec(char *s1);
char				*ft_free_join(char *str1, char *str2, int i);
char				*ft_strlcpy(char *dst, const char *src, int *len);
char				*helpinsub(pid_t pid, int q, int fds[2]);
char				*lastcheck(char *a, char *b);
char				*mathabort(char **s, char **tmp);
char				*mathaction(char **s, int i, t_var *var, t_par *par);
char				*mathcore(char *s, t_var *var, t_par *par);
t_par				*newelem(t_par *tmp);
char				*parse_subshell(char *cmd, t_var **var, int q);
char				*read_fd(int fd, int quotes);
char				*readcase(t_par *cur, char **buf, int s);
char				*retenv(t_env *env, char *occur);
char				*schrnob(char *s, char c);
t_av				*splitsub(t_par *cur, t_av **av, int *f);
char				*substitute(char *first, char *last);
char				*transform_list_to_char(t_av *temp);
char				*trncat(char *tr, char *s);
char				*writeresult(long long r, char **s, int j);
void				actualize_env(t_var **var);
int					add_fnc(t_var **lst, char *name, char *line, int i);
int					alldigit(char *s);
void				aroundmaths(char **tmp, char **s, char **s2, int *i);
int					assignation(char *ope, long long l[3], char *v, t_var *var);
int					assigntovar(int r, char *v, t_var *var);
int					askpid(char *s, int *i, char **cp, int *a);
int					avdelim(char **s, t_par **par, int *brk, int st);
void				bofg(int pid, int *r, t_par *cur, int fd[2]);
int					brackets(char **s, int i, t_par *cur, int r);
int					brkcase(t_par *cur);
void				buildtabav(t_par **par, int f);
int					builtin_command(t_par **par, t_var **var, int fds[2]);
int					bwise(char *s);
int					calcul(char *ope, long long l[3]);
int					calcul2(char *ope, long long l[3]);
void				changehead(t_av **take, t_av **give);
void				changelast(t_av **take, t_av **give);
char				chardelim(char *s);
int					check_if_fnc(char *line, t_var **lst, int flag);
int					checkav(t_av **av);
int					checkifpreviouslnk(char *s);
int					checkpid(void);
int					checkvarname(char *s);
int					chkredir(char *s);
int					chooseop(char **s, t_var *var, t_par *par);
int					ckfav(t_par **cur, int i);
int					ckbrs(char *s, char **core);
int					ckbrs2(char *s, int j);
int					ckcglob(char *s, int i, int *a);
int					ckhks(char *s, int i, int ec[3]);
int					ckop(char *s);
int					ckvar(char *t);
void				cleanbrk(t_par **cur, t_par **tmp, char *buf, int brk);
void				cleanlist(t_av **av);
int					comparaison(char *ope, long long l[3]);
int					cpu(char *d, char *s, int *i);
int					createfds(t_par *cur, t_var *var, int c, int d);
int					dealwfds1(t_par *cur, int fd[2]);
void				dealwfds2(t_par **cur);
int					dealwopt(char *av, t_var *var);
int					digit(int *brk, char *s, t_par *par);
int					display_env(t_env *env);
int					display_export(t_var **lst, t_par **par, t_av **av);
int					dofork(t_par *cur, int r);
int					dupinsidefork(t_par *cur, int fd[2]);
void				endofexec(t_par **cur, int pid, int fd[2]);
void				endofmloop(char **tmp, int *c, int *i);
int					env_strequ(char const *s1, char const *s2);
void				envvarcase(int *i, t_par *cur);
void				envvarcasep2(int *i, int a, int b, t_par *cur);
int					eval(char **cmdline, t_var **var);
void				exec(t_var *var, char *m, t_par *cur);
int					execf(t_var **var, t_par *cur);
int					exsub(t_par *cur, t_var *var);
void				fgend(int pdid, int *r, int fd[2]);
void				fillav(t_par *cur, char *buf, int e, int s);
int					find_str(char *name, char *find);
int					fine(char *s, int i, int c, int j);
int					finep1(char *s, int *i, int *c, int *j);
int					finep2(char *s, int *i, int *c, int *j);
int					fncheck(t_var **var, t_par *cur);
int					fope(char *s);
void				forkaction(t_par *cur, t_var *var, int fd[2]);
void				freeavs(t_par **list);
void				freevar(t_var *var);
void				freefds(void);
int					ft_export(t_var **lst, char *to_find, char *line, int flag);
void				ft_list_clear(t_env **begin_list);
int					ft_list_nchange_if(t_var **var, char *data_ref,
					int (*equ)(), int n);
int					ft_list_remove_if(t_env **begin_list, char *data_ref,
					int (*equ)());
void				ft_plist_clear(t_par **begin_list);
int					fthope(char *s);
void				giverealname(char **mydir, char *av);
int					gonext(t_par **cur, char **tofree);
int					handle_dirissue(char ac, t_av *av, t_var *var);
void				handledots(char **s, int i, int t, int l);
int					hckp(char *s, int i);
int					helpaggreg(t_par *cur, int c);
int					helpbrackets(char **s, int *i, t_par **par, t_var **var);
int					helpbrackets2(char **s, int *i, t_par *par);
int					helpchkivar(int f, int h, t_var **var, char *s);
void				helpinvar(char *s, char o, t_var *var, t_par *par);
void				helpmact(char *v, char tr[LINE_MAX], int t[3]);
void				helpmact2(t_var *var, char tr[LINE_MAX], t_par *par,
					long long *r);
int					helpquotes(char **s, int *i, t_par *par, t_var **var);
void				helpshlvl(char *s);
void				helptosub(char **s, int *i, t_par *par, t_var *var);
int					heredoc(t_par *cur);
int					incremvar(char *s, t_var *var, char c, t_par *par);
void				initdup(t_par *cur, int fd[2]);
int					isbkslsh(char **s, int *i);
int					isope(char *s);
int					isstrfine(char **s);
void				isvar(char **s, t_var *var, t_par *par, int *a);
int					lope(char *s);
int					listlen(t_env *list);
long long			mact(char *s, int i, t_var *var, t_par *par);
void				mvtbin(int i, t_par *cur);
int					nbcks(char *s, int b);
void				newav(t_par *cur, char *buf, int e, int s);
int					newbuf(char *buf, int *brk, t_par **cur);
int					newpid(void);
int					noblank(char *buf);
int					nofork(t_par *cur);
void				nopaths(int opt[2], t_env *tmp, t_var **var);
void				nopwdcase(t_env **tmp, t_env **head, int a);
void				noshlvlcase(t_env **tmp, t_env **head, int a);
int					notthisone(t_par *cur);
int					onebyone(char **s, t_var *var, int i, int a);
int					onec(int *brk, char *s, t_par *par);
int					onlyspaces(char *s);
int					openerror(t_par *cur);
int					openfile(t_par *cur);
int					outofrec(char **s, int *i, char c, t_par *cur);
int					outofrecfd(char **new, int *p, char c, t_par *cur);
int					parseline(char **buf, t_par **par);
int					parserror(t_par *cur, char *buf, int s);
void				pathstat(int *c, char **mydir, char *av, struct stat *s);
void				pipensavemax(int fd[2]);
void				pushfd(t_par *cur);
char				quoted(char *s, int i);
int					readheredoc(t_par *cur);
int					readvar(t_par *cur, t_var **var, int fd, int fds[2]);
int					removeifsame(t_env **begin_list, char *data_ref,
					int (*cmp)());
int					rewriteavs(t_par **cur, t_var *var, int i, int f);
int					setnewenv(int ac, t_av *av, t_env **head, int a);
int					skipquotes(char **s, int i, t_par *curi, int r);
int					sope(char *s);
int					subinmath(char **s, t_par *par, t_var *var);
void				startfromroot(char **s);
int					status(t_par *cur, int fd[2]);
int					sthope(char *s);
int					stillckglob(int a);
int					takeaction(t_par **par, t_var *var, t_par *cur);
int					toforkornot(t_par *cur, t_var *var, int fd[2]);
int					tope(char *s);
void				transferavs(t_par **par, t_par **cur, int c, t_var *var);
int					unset(t_par *par, t_var **lst);
int					unsetenvv(t_par *cur, t_env **env);
int					vfope(char **s, int *c);
void				whichfd(t_par *cur, int *fd, int fds[2], t_av **save);
char				wdelim(char *s, int *i, t_par *cur);
int					wop(int op, int (**ope)(char *));
int					wr(int r, char **cp, int *a);
int					writeonfile(t_par *cur, int c);
int					wtdwenv(t_par *par, t_var **var);
int					wstruct(t_var *var, char **cp, int *a, char *tmp);
#endif
