/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:16:16 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/17 15:02:48 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnumeric(char *str)
{
	long	number;
	int		i;

	i = 0;
	if (str[i] && str[i + 1] && (str[i] == '-' || str[i] == '+' ))
		i++;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	if (i > 11)
		return (0);
	number = ft_atoi(str);
	if (number > 2147483647 || number < -2147483648)
		return (0);
	return (1);
}

int	exec_exit(t_sh *sh, t_arg *arg)
{
	int	exit_status;

	exit_status = 0;
	if (arg)
	{
		if (ft_isnumeric(arg->value))
		{
			if (arg->next)
				return (ft_printf_fd(2, "%s exit: too many arguments\n",
						PROMPT), 1);
			else
				exit_status = ft_atoi(arg->value) % 255;
		}
		else
		{
			ft_printf_fd(2, "%s exit: %s: numeric argument required\n",
				PROMPT, arg->value);
			exit_status = 2;
		}
	}
	close_fd_io(sh);
	sh_free_all(sh);
	exit(exit_status);
}
