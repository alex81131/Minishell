/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:53:17 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/06 17:53:17 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh	*init_sh(char	**env)
{
	t_sh	*sh;

	sh = (t_sh *)malloc(sizeof(t_sh) * 1);
	if (!sh)
		return (NULL);
	sh->env = create_env_list(env);
	if (!sh->env)
	{
		free(sh);
		return (NULL);
	}
	sh->fd_in = STDIN_FILENO;
	sh->fd_out = STDOUT_FILENO;
	sh->cmd = NULL;
	sh->pids = NULL;
	sh->cmd_count = 0;
	sh->pid_count = 0;
	sh->exit_code = 0;
	return (sh);
}

void	sh_free_token(t_sh *sh, t_token *token)
{
	if (token)
		tok_free(token);
	if (sh)
	{
		if (sh->cmd)
		{
			bld_free(sh->cmd);
			sh->cmd = NULL;
		}
		if (sh->pids)
		{
			free(sh->pids);
			sh->pids = NULL;
		}
	}
}

void	sh_free_all(t_sh *sh)
{
	if (sh)
	{
		if (sh->cmd)
			bld_free(sh->cmd);
		if (sh->env)
			env_free(sh->env);
		if (sh->pids)
			free(sh->pids);
		free(sh);
	}
	rl_clear_history();
}
