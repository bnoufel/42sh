/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:11:10 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:11:12 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LIBFT_H
# define __LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

typedef struct			s_listlibft
{
	void				*content;
	size_t				content_size;
	struct s_listlibft	*next;
}						t_listlibft;

char					**ft_sstrdup(char **s1);
char					**ft_strsplit(char const *s, char c);
char					*dupspec(char *s1);
char					*ft_chardup(const char s1);
char					*ft_chardup_spec(const char s1);
char					*ft_itoa(int n);
char					*ft_lltoa(long long n);
char					*ft_lltoa_base(long long n, int base);
t_listlibft				*ft_lstnew(void const *content, size_t content_size);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strchr(const char *s, int c);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strdup(const char *s1);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strjoinfree(char *s1, char *s2, size_t tofree);
char					*ft_strlcpy(char *dst, const char *src, int *len);
char					*ft_strncpy(char *dst, const char *src, size_t len);
char					*ft_strnew(size_t size);
char					*ft_strrchr(const char *s, int c);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strsub(char const *s, unsigned int start,
						size_t len);
char					*lltoa(long long n);
int						ft_atoc(const char *s, int *c);
int						ft_atoi(const char *str);
long					ft_atol(const char *str);
long long				ft_atoll(const char *str);
void					ft_bzero(void *s, size_t n);
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isspace(int c);
long long				ft_iterative_power(long long nb, long long power);
int						ft_strcmp(const char *s1, const char *s2);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_putchar(char c);
void					ft_putchar_fd(char c, int fd);
void					ft_putendl(char const *s);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr(int n);
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr(char const *s);
void					ft_putstr_fd(char const *s, int fd);
size_t					ft_sstrlen(char **str);
void					ft_strclr(char *s);
void					ft_strdel(char **as);
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
int						isbin(char *s);
int						sisdigit(char *s);

#endif
