/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:30:25 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/11 15:39:40 by tkaragoz         ###   ########.fr       */
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

void	free_all_sh(t_sh *sh)
{
	if (sh)
	{
		if (sh->cmd)
			free_cmd(sh->cmd);
		if (sh->pids)
			free_pids(sh->pids);
		if (sh->env)
			env_free(sh->env);
	}
}
