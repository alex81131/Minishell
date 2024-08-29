/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:57:27 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/23 09:57:27 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	right_fd(size_t *i)
{
	size_t	j;

	j = 0;
	while (sh()->cmd[*i][j + 1] && sh()->redir[*i] == '>' \
								&& sh()->redir[*i] == 'd')
		j++;
	return (j);
}

static void	here_doc(char *delimiter)
{
	int		p_fd[2];
	pid_t	pid;
	char	*line;

    ft_printf_fd(2, "[In here_doc]\n");
	if (pipe(p_fd) == -1)
		ft_exit(EXIT_FAILURE, 0);
	pid = fork();
	if (pid == -1)
		ft_exit(EXIT_FAILURE, 0);
	if (pid == 0)
	{
		close(p_fd[0]);
		while (1)
		{
			ft_putstr_fd("heredoc> ", STDOUT_FILENO);
			line = get_next_line(STDIN_FILENO);
			if (!line || ft_strcmp(line, delimiter) == 0)
				break;
			ft_putstr_fd(line, p_fd[1]);
			free(line);
		}
		free(line);
		close(p_fd[1]);
		exit(0);
	}
	else
	{
		close(p_fd[1]);
		if (dup2(p_fd[0], STDIN_FILENO) == -1)
			ft_exit(EXIT_FAILURE, 0);
		close(p_fd[0]);
		wait(NULL);
	}
}

void	left_redir(size_t *i)
{
	int		fd;
	size_t	j;

	j = (*i)++;
	sh()->stdin_bkp = dup(STDIN_FILENO);
	while (sh()->redir[*i] == '<' || sh()->redir[*i] == 'h')
	{
		if (sh()->redir[*i] == '<')
		{
            ft_printf_fd(2, "[In <]\n");
			fd = open(sh()->cmd[*i][0], O_RDONLY);
			if (fd == -1)
				ft_exit(EXIT_FAILURE, *i);
			close(fd);
			(*i)++;
		}
		else if (sh()->redir[*i] == 'h')
		{
            ft_printf_fd(2, "[In here_doc]\n");
			here_doc(sh()->cmd[*i][0]);
			(*i)++;
		}
	}
	fd = open(sh()->cmd[*i][right_fd(i)], O_RDONLY);
	if (fd == -1)
		ft_exit(EXIT_FAILURE, *i);
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_exit(EXIT_FAILURE, *i);
	close(fd);
	dup2(STDIN_FILENO, sh()->stdin_bkp);
	close(sh()->stdin_bkp);
	if (sh()->redir[*i] && (sh()->redir[*i] == '>' || sh()->redir[*i] == 'd'))
		right_redir(&j);
	if (sh()->redir[*i])
		redirect(sh()->fd[1], STDOUT_FILENO);
	ft_exec(j);
}
