/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:04:07 by bnoufel           #+#    #+#             */
/*   Updated: 2018/10/18 16:04:11 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HASH_H
# define __HASH_H

typedef struct		s_bin
{
	char			*name;
	char			*path;
	unsigned long	hash;
	struct s_bin	*next;
}					t_bin;

typedef struct		s_hash
{
	char			*name;
	char			*path;
	struct s_hash	*next;
}					t_hash;
size_t				ft_size_bin(t_bin *bin);
void				get_binaries(t_bin **bin, t_env *env);
char				*get_hash(char *bin);
t_hash				**create_tab(t_env *env);
unsigned long		hash(char *str);
void				clean_bin(void);
void				clean_tab(void);
t_bin				*ft_create_elem(t_bin *lst, char *name, char *path);
void				*ft_create_elem_hash(t_hash *lst, char *name, char *path);
#endif
