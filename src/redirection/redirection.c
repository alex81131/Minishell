/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:54:42 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/23 08:54:42 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
        printf("Redirecting from %d to %d\n", oldfd, newfd);
		if (dup2(oldfd, newfd) == -1)
		{
			perror("dup2");
			close(oldfd);
			exit(EXIT_FAILURE);
		}
	}
}

static void	exec_child(size_t i, int in_fd)
{
	close(sh()->fd[0]);
	redirect(in_fd, STDIN_FILENO);
	if (sh()->redir[i] == '>' || sh()->redir[i] == 'd')
		right_redir(&i);
	else if (sh()->redir[i] == '<')
		left_redir(&i);
	else
	{
		redirect(sh()->fd[1], STDOUT_FILENO);
		ft_exec(i);
	}
	close(sh()->fd[1]);
	exit(EXIT_SUCCESS);
}

static void	exec_parent(size_t i, int in_fd)
{
	size_t	j;

	j = i;
	if (i > 0)
		close(in_fd);
	close(sh()->fd[1]);
	while (sh()->redir[i] && sh()->redir[i] != '|')
		i++;
	if (ft_strchr(sh()->redir + j, '|'))
		i++;
	redirection(i, sh()->fd[0]);
}

static void	pipe_and_fork(size_t i, int in_fd)
{
	pid_t	pid;

	sh()->stdin_bkp = dup(STDIN_FILENO);
	if (sh()->stdin_bkp == -1 || pipe(sh()->fd) == -1)
		ft_exit(EXIT_FAILURE, i);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		exec_child(i, in_fd);
}

void	redirection(size_t i, int in_fd)
{
	if (!sh()->cmd[i + 1])
	{
		if (i > 0)
			final_redir(i, in_fd);
		else
			lonely_command(i, in_fd);
	}
	else
	{
		pipe_and_fork(i, in_fd);
		wait(NULL);
		exec_parent(i, in_fd);
	}
	if (dup2(sh()->stdin_bkp, STDIN_FILENO) == -1)
	{
		perror("dups2");
		exit(EXIT_FAILURE);
	}
	close(sh()->fd[0]);
	close(sh()->stdin_bkp);
}
