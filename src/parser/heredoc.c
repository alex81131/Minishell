/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:00:21 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/06 16:00:21 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ps_heredoc_return(void)
{
	if (g_signal.end_heredoc == 1)
	{
		g_signal.end_heredoc = 0;
		return (1);
	}
	return (0);
}

static int	ps_ini_heredoc(int fd, char *eof)
{
	char	*line;

	signal(SIGINT, sig_heredoc);
	while (1)
	{
		line = readline("here_doc>");
		if (!line)
		{
			ft_printf_fd(2, \
				"Minishell: here_doc: called end-of-line (ctrl-d)\n");
			break ;
		}
		if (!ft_strcmp(line, eof) || g_signal.end_heredoc == 1)
		{
			free(line);
			break ;
		}
		ft_printf_fd(fd, "%s\n", line);
		free(line);
	}
	return (ps_heredoc_return());
}

int	ps_analyze_heredoc(t_token *token)
{
	char	*filename;
	int		fd;
	int		end;

	end = 0;
	while (token && !end)
	{
		if (token->type == HEREDOC)
		{
			filename = ms_generate_random(token->next->value);
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (!fd)
				return (1);
			if (ps_ini_heredoc(fd, token->next->value))
				end = 1;
			close(fd);
			free(token->next->value);
			token->next->value = filename;
			token->type = N_HEREDOC;
		}
		token = token->next;
	}
	return (end);
}

void	ps_unlink_err(t_token *token)
{
	while (token)
	{
		if (token->type == N_HEREDOC)
			unlink(token->next->value);
		token = token->next;
	}
}
// ps_unlink_err unlinks/deletes the file created for here_doc
// 	(token->next->value = filename)
// 	with the presence of error in here_doc.