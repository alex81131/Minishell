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

t_sh	*ms_ini_sh(char **env)
{
	t_sh	*sh;

	sh = (t_sh *)malloc(sizeof(t_sh));
	if (!sh)
		return (NULL);
	sh->env = ms_env_dup(env);
	if (!sh->env)
	{
		free(sh);
		return (NULL);
	}
	sh->def_in = STDIN_FILENO;
	sh->def_in = STDOUT_FILENO;
	sh->exe = NULL;
	sh->pid = NULL;
	sh->exe_count = 0;
	sh->pid_count = 0;
	sh->exit_code = 0;
	return (sh);
}

void	ms_free_token(t_sh *sh, t_token *token)
{
	if (token)
		tok_free(token);
	if (sh)
	{
		if (sh->exe)
		{
			bld_free(sh->exe);
			sh->exe = NULL;
		}
		if (sh->pid)
		{
			free(sh->pid);
			sh->pid = NULL;
		}
	}
}

void	ms_free_all(t_sh *sh)
{
	if (sh)
	{
		if (sh->exe)
			bld_free(sh->exe);
		if (sh->env)
			env_free(sh->env);
		if (sh->pid)
			free(sh->pid);
		free(sh);
	}
	rl_clear_history();
}

int	ms_check_line(char *line)
{
	if (line[0] == '\0')
		return (1);
	return (0);
}
