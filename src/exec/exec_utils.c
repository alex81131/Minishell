/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:30:25 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/10 19:02:36 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd_p(int *fd)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}

void	close_fd_io(t_sh *sh)
{
	if (sh->fd_in != -1)
		close(sh->fd_in);
	if (sh->fd_out != -1)
		close(sh->fd_out);
}

void	unlink_heredocs(t_sh *sh)
{
	t_cmd		*cmd;
	t_filenames	*files;

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

void	free_all_sh(t_sh *sh)
{
	if (sh)
	{
		if (sh->cmd)
			free_cmd(sh->cmd);
		if (sh->pids)
			free_pids(sh->pids);
		if (sh->env)
			env_free(sh->env)
	}
}
