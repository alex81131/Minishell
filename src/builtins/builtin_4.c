/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:16:16 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/11 18:16:22 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(char *str)
{
	ft_putstr_fd("minishell> exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

int	exec_exit(t_cmd *cmd, t_env *env)
{
	int	exit_status;

	exit_status = 0;
	printf("exit\n");
	if (cmd[1])
	{
		if (ft_isnumeric(cmd[1]))
		{
			if (cmd[2])
				return (ft_putendl_fd("minishell> exit: too many arguments",
						STDERR_FILENO), 1);
			else
				exit_status = ft_atoi(cmd[1]) % 255;
		}
		else
		{
			exit_error(cmd[1]);
			exit_status = 2;
		}
	}
	env_free(env);
	exit(exit_status);
}
