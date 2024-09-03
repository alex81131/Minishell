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

static int	init_record(int start)
{
	if (start == -1)
		return (1);
	return (0);
}

static int	right_fd(size_t *i)
{
	size_t	j;

	j = 0;
	while (sh()->cmd[*i][j + 1] && (sh()->redir[*i] == '>' \
								|| sh()->redir[*i] == 'd'))
		j++;
	return (j);
}

void	left_redir(size_t *i)
{
	int		fd;
	char	last;
	int		h1;
	int		h2;

	sh()->stdin_bkp = dup(STDIN_FILENO);
	h2 = -1;
	while (sh()->redir[*i] && (sh()->redir[*i] == '<' || sh()->redir[*i] == 'h'))
	{
		if (sh()->redir[(*i)++] == '<')
		{
			fd = open(sh()->cmd[*i][0], O_RDONLY);
			if (fd == -1)
				ft_exit(EXIT_FAILURE, *i);
			close(fd);
			last = '<';
		}
		else if (sh()->redir[(*i)++] == 'h')
		{
			last = 'h';
			h1 = h2;
			h2 = *i;
		}
	}
	if (last == '<')
	{
		fd = open(sh()->cmd[*i][right_fd(i)], O_RDONLY);
		if (fd == -1)
			ft_exit(EXIT_FAILURE, *i);
	}
	else if (last == 'h')
		here_doc(h1, h2);///////Need work
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
/*
When handling multiple in-/output redirections,such as
	in cat < in1 < in2,
	echo "Hello" >out1 >out2,
	the shell should only use the last redirection
	to provide the input to the command.
Multiple <<:
	only the last 2 count as the beginning and the end of the here_doc.
	ie. cat <<h1 <<h2 <<h3 << h4
	1, h1, 2, h2, 3, h3, 4, h4
	there'd be only 4 recorded.
When < and << are mixed together, whoever comes last counts.
	But if there's here_doc, it still pops up,
	but will only be recorded if it's the last redirection.
*/
/*
*i is used for cmd[*i] in 
	else if (sh()->redir[(*i)++] == 'h')
	so automatically *i is +1 to correctly point the right command
*/