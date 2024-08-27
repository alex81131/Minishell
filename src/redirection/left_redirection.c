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

void	left_redir(size_t *i)
{
	int		fd;
	size_t	j;

	j = (*i)++;
	sh()->stdin_bkp = dup(STDIN_FILENO);
	while (sh()->redir[*i] == '<')
	{
		fd = open(sh()->cmd[*i][0], O_RDONLY);
		if (fd == -1)
			ft_exit(EXIT_FAILURE, *i);
		close(fd);
		(*i)++;
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
