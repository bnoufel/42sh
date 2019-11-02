/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:59:42 by golliet           #+#    #+#             */
/*   Updated: 2018/10/18 16:01:14 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char		*prompt_commit(char *line)
{
	int			i;
	char		*commit;

	commit = NULL;
	if (!(commit = (char *)malloc(sizeof(char) * 10)))
		malloc_failed("prompt commit");
	i = 0;
	while (i < 8)
	{
		commit[i] = line[i];
		i++;
	}
	commit[i] = ' ';
	commit[i + 1] = '\0';
	ft_strdel(&line);
	return (commit);
}

static void		prompt_git_branch_info(char *branch, char **prompt)
{
	int			fd;
	char		*line;
	t_stat		st;

	if (stat(branch, &st) == -1)
	{
		free(branch);
		return ;
	}
	if ((fd = open(branch, O_RDONLY)) > -1)
	{
		if ((gnl(fd, &line, 1)) > 0)
		{
			if (!(*prompt = ft_strjoinfree((*prompt), "\033[0m    ", 1)))
				malloc_failed("prompt git info");
			line = prompt_commit(line);
			if (!(*prompt = ft_strjoinfree((*prompt), line, 3)))
				malloc_failed("prompt git info");
		}
		while (gnl(fd, &line, 1))
			ft_strdel(&line);
		close(fd);
		free(branch);
	}
}

static void		prompt_git_info(char *branch, char **prompt)
{
	int			fd;
	char		*line;
	t_stat		st;

	prompt_git_branch_info(branch, prompt);
	if (stat("./.git/COMMIT_EDITMSG", &st) == -1)
		return ;
	if ((fd = open("./.git/COMMIT_EDITMSG", O_RDONLY)) != -1)
	{
		if ((gnl(fd, &line, 1)) == 1)
		{
			if (!(*prompt = ft_strjoinfree((*prompt), "\033[0m", 1)))
				malloc_failed("prompt git info");
			if (!(*prompt = ft_strjoinfree((*prompt), "\"", 1)))
				malloc_failed("prompt git info");
			if (!(*prompt = ft_strjoinfree((*prompt), line, 1)))
				malloc_failed("prompt git info");
			if (!(*prompt = ft_strjoinfree((*prompt), "\"", 1)))
				malloc_failed("prompt git info");
		}
		ft_strdel(&line);
		while (gnl(fd, &line, 1) > 0)
			free(line);
		close(fd);
	}
}

static void		help_prompt_git(char **prompt, char **line, char **branch)
{
	if (!(*prompt = ft_strjoinfree((*prompt), CYAN, 1)))
		malloc_failed("prompt git");
	if (!(*prompt = ft_strjoinfree((*prompt), ft_return_home(*line), 1)))
		malloc_failed("prompt git");
	if (!(*branch = ft_strjoin("./.git/refs/heads/", ft_return_home(*line))))
		malloc_failed("prompt");
	ft_strdel(line);
}

void			prompt_git(char **prompt)
{
	t_stat		st;
	char		*line;
	int			fd;
	char		*branch;

	branch = NULL;
	if (stat("./.git", &st) > -1)
	{
		if (!((*prompt) = ft_strjoinfree((*prompt),
			"\x1b[37;1m on \033[0mgit:", 1)))
			malloc_failed("prompt git");
		if (stat("./.git/HEAD", &st) == -1)
			return ;
		if ((fd = open("./.git/HEAD", O_RDONLY)) > -1)
		{
			if ((gnl(fd, &line, 1)) == 1)
				help_prompt_git(prompt, &line, &branch);
			while (gnl(fd, &line, 1))
				ft_strdel(&line);
			close(fd);
		}
		prompt_git_info(branch, prompt);
	}
}
