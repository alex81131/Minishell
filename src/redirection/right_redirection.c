/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:12:23 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/23 10:12:23 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wrap_openning_fd(int fd, size_t j, size_t *i)
{
	if (sh()->redir[*i] == 'd')
		fd = open(sh()->cmd[*i][0], O_CREAT);
	else
		fd = open(sh()->cmd[*i][0], O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_exit(EXIT_FAILURE, *i);
	if (sh()->cmd[*i][1])
		sh()->cmd[j] = ft_arrjoin(sh()->cmd[j], sh()->cmd[*i] + 1);
	(*i)++;
}

static void	skip_next_left_redir(size_t *i)
{
	int	fd;

	while (1)
	{
		fd = open(sh()->cmd[*i][0], O_RDONLY);
		if (fd == -1)
			ft_exit(EXIT_FAILURE, *i);
		close(fd);
		(*i)++;
		if (sh()->redir[*i] == '<' || sh()->redir[*i] == 'd')
			break ;
	}
}

void	right_redir(size_t *i)
{
	int		fd;
	size_t	j;

	fd = 0;
	j = (*i)++;
	while (sh()->redir[*i] == '>' && sh()->redir[*i] == 'd')
		wrap_openning_fd(fd, j, i);
	if (sh()->cmd[*i][1])
		sh()->cmd[j] = ft_arrjoin(sh()->cmd[j], sh()->cmd[*i] + 1);
	if (sh()->redir[*i - 1] == 'd')
		fd = open(sh()->cmd[*i][0], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd = open(sh()->cmd[*i][0], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_exit(EXIT_FAILURE, *i);
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_exit(EXIT_FAILURE, *i);
	sh()->fd[1] = fd;
	redirect(sh()->fd[1], STDOUT_FILENO);
	(*i)++;
	if (sh()->redir[*i] == '<' || sh()->redir[*i] == 'd')
		skip_next_left_redir(i);
	ft_exec(j);
}
