/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mysh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidelefo <lidelefo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:01:00 by lidelefo          #+#    #+#             */
/*   Updated: 2018/10/18 16:01:01 by lidelefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MYSH_H
# define __MYSH_H
# include <dirent.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <unistd.h>
# include <termios.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/param.h>
# include <limits.h>
# include <pwd.h>
# include <grp.h>
# include "libft.h"
# include "minishell.h"
# include "glob.h"
# include "hash.h"
# include "myterm.h"
# include "jobs.h"
# include "equalizer.h"
# include "script.h"
# define RED		"\x1b[1;31m"
# define GREEN		"\x1b[1;32m"
# define YELLOW		"\x1b[1;33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[1;36m"
# define BGCYAN		"\x1b[30;46m"
# define PINK		"\x1b[35m"
# define BGYELLOW	"\x1b[30;43m"
# define BGGREEN	"\x1b[30;42m"
# define BGRED		"\x1b[41m"
# define RESET		"\x1b[0m"

typedef struct passwd	t_passwd;
typedef struct group	t_group;
typedef struct stat		t_stat;
void		malloc_failed(char *prog);
char		*checkinfo(t_var **var, t_cursor *cursor, char hostname[256]);
int			helploop(char **buff, int *rd, t_cursor *cursor);
void		helploop2(char *buf, t_list **list, t_cursor *cursor,
			t_var *var);
void		loop(t_cursor *cursor, t_var *var);
void		close_fdmax(void);
#endif
