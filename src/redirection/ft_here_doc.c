/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:51:40 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/03 20:51:40 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_record(int start)
{
	if (start == -1)
		return (1);
	return (0);
}

static int	check_end_condition(char *line, int end, int record)
{
	if (record && !ft_strcmp(line, sh()->cmd[end][0]))
	{
		free(line);
		return (1);
	}
	return (0);
}

static int	here_doc_read(int p_fd[2], int start, int end, int record)
{
	char	*line;
	int		end_found;

	end_found = 0;
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (check_end_condition(line, end, record))
		{
			end_found = 1;
			break ;
		}
		if (!record && ft_strcmp(line, sh()->cmd[start][0]) == 0)
		{
			record = 1;
			free(line);
			continue ;
		}
		if (record)
			ft_printf_fd(p_fd[1], "%s\n", line);
		free(line);
	}
	return (end_found);
}

static void	handle_child(int p_fd[2], int start, int end, int record)
{
	int	end_found;

	close(p_fd[0]);
	end_found = here_doc_read(p_fd, start, end, record);
	close(p_fd[1]);
	if (end_found)
		exit(0);
	else
		exit(1);
}

void	here_doc(int start, int end)
{
	int		p_fd[2];
	pid_t	pid;
	int		record;
	int		status;

	record = init_record(start);
	if (pipe(p_fd) == -1)
		ft_exit(EXIT_FAILURE, 0);
	pid = fork();
	if (pid == -1)
		ft_exit(EXIT_FAILURE, 0);
	if (pid == 0)
		handle_child(p_fd, start, end, record);
	else
	{
		close(p_fd[1]);
		if (dup2(p_fd[0], STDIN_FILENO) == -1)
			ft_exit(EXIT_FAILURE, 0);
		close(p_fd[0]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			ft_exit(EXIT_FAILURE, 0);
	}
}
/*
Original:

static void	here_doc_read(size_t start, size_t end, int	record)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break;
		if (record && !ft_strcmp(line, sh()->cmd[end][0])))
		{
			end_found = 1;
			free(line);
			break;
		}
		if (h_count > 1 && ft_strcmp(line, sh()->cmd[start][0]) == 0)
		{
			record = 1;
			free(line);
			continue ;
		}
		if (record)
			ft_printf_fd(p_fd[1], "%s\n", line);
		free(line);
	}
}
*/