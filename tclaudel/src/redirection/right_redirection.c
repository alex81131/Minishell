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

static void	wrap_openning_fd(int fd, size_t save, size_t *i)
{
	if (sh()->redir[*i] == 'd')
		fd = open(sh()->cmd[*i][0], O_CREAT);
	else
		fd = open(sh()->cmd[*i][0], O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_exit(EXIT_FAILURE, *i);
	if (sh()->cmd[*i + 1])
		sh()->cmd[save] = ft_arrjoin(sh()->cmd[save], sh()->cmd[*i + 1]);
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
	int	fd;
	int	save;

	fd = 0;
	save = *i;
	while (sh()->redir[*i] == '>' || sh()->redir[*i] == 'd')
		wrap_openning_fd(fd, save, i);
    int k = 0;
    while(sh()->cmd[k])
    {
        int j = 0;
        while (sh()->cmd[k][j])
        {
            printf("sh()->cmd[%d][%d] = %s\n", k, j, sh()->cmd[k][j]);
            j++;
        }
        k++;
    }
	if (sh()->redir[*i] == 'd')
		fd = open(sh()->cmd[*i + 1][0], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd = open(sh()->cmd[*i + 1][0], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_exit(EXIT_FAILURE, *i + 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_exit(EXIT_FAILURE, *i + 1);
	sh()->fd[1] = fd;
	redirect(sh()->fd[1], STDOUT_FILENO);
	if (sh()->redir[*i + 1] && (sh()->redir[*i + 1] == '<' || sh()->redir[*i] == 'd'))
		skip_next_left_redir(i);
	ft_exec(*i);
}
