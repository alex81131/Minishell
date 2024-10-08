/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:53:12 by kyeh              #+#    #+#             */
/*   Updated: 2024/08/12 19:53:12 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	static int	pid;

	if (sig == 0 || sig > 32)
	{
		pid = sig;
		return ;
	}
	if (sig == SIGINT || sig == SIGQUIT)
	{
		if (pid)
		{
			kill(pid, sig);
			if (sig == SIGQUIT)
				ft_printf("Quit: 3\n", pid);
		}
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	child_sigint(int sig)
{
	(void)sig;
	write(0, "\n", 1);
	write(1, "\n", 1);
}

void	sign_init(void)
{
	signal(SIGQUIT, handle_sigint);
	signal(SIGINT, handle_sigint);
}
