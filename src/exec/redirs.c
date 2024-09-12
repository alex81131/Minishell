/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:28:48 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/12 15:58:49 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_heredocs(t_sh *sh)
{
	t_cmd		*cmd;
	t_filename	*files;

	cmd = sh->cmd;
	while (cmd)
	{
		files = cmd->redirs;
		while (files)
		{
			if (files->type == N_HEREDOC)
				unlink(files->name);
			files = files->next;
		}
		cmd = cmd->next;
	}
}

static void	redir_files(t_cmd *cmd, t_filename *file)
{
	if (file->type == INFILE || file->type == N_HEREDOC)
	{
		if (cmd->fd_in != STDIN_FILENO)
			close (cmd->fd_in);
		cmd->fd_in = open(file->name, O_RDONLY);
		if (cmd->fd_in == -1)
			ft_printf_fd(STDERR_FILENO, "Minishell: %s: %s\n", file->name, strerror(errno));
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	else
	{
		if (cmd->fd_out != STDOUT_FILENO)
			close (cmd->fd_out);
		if (file->type == OUTFILE)
			cmd->fd_out = open (file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file->type == APPEND)
			cmd->fd_out = open (file->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->fd_out == -1)
			ft_printf_fd(STDERR_FILENO, "Minishell: %s: %s\n", file->name, strerror(errno));
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

int	handle_files(t_cmd *cmd)
{
	t_filename	*tmp;

	tmp = cmd->redirs;
	while (tmp)
	{
		redir_files(cmd, tmp);
		if (cmd->fd_in == -1 || cmd->fd_out == -1)
			return (EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
