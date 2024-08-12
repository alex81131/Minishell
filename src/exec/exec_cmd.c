/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:04:03 by kyeh              #+#    #+#             */
/*   Updated: 2024/08/12 20:04:03 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_sh *sh, char **cmd)
{
	size_t	i;
	char	*current_cmd;
	char	**env_cpy;

	i = 0;
	env_cpy = cpy_env(sh->env);
	if (execve(cmd[0], cmd, env_cpy) == -1)
	{
		current_cmd = ft_strjoin_free("/", cmd[0], 2);
		while (sh->path && sh->path[i])
		{
			cmd[0] = ft_strjoin_free(sh->path[i], current_cmd, 0);
			execve(cmd[0], cmd, env_cpy);
			i++;
			free_string(&cmd[0]);
		}
		if (errno == ENOENT)
			ft_printf_fd(2, "Minishell: %s: Command not fouind.\n", \
							current_cmd + 1);
		else
			ft_printf_fd(2, "%s\n", strerror(errno));
		free_array(env_cpy);
		free_string(&current_cmd);
		exit(127);
	}
}
/*
exit(127) typically signifies that a command or executable could not be found.
*/