/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:28:48 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/06 18:28:48 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

static void	sig_interrupt(int status)
{
	(void)status;
	if (g_signal.signal_code != 1)
	{
		g_signal.signal_code = SIGNAL_OFFSET + SIGINT;
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_initiate(void)
{
	rl_event_hook = sig_event;
	signal(SIGINT, sig_interrupt);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	sig_heredoc(int status)
{
	(void)status;
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
	g_signal.end_heredoc = 1;
	g_signal.signal_code = SIGNAL_OFFSET + SIGINT;
}

void	sig_exec(int status)
{
	(void)status;
	g_signal.signal_code = SIGNAL_OFFSET + SIGINT;
	write(STDERR_FILENO, "\n", 1);
}
// sig_initiate:
// 	rl_event_hook:
// 		assign a function to be triggered whenever Readline handles
// 		an input event (e.g., displaying the prompt, processing input)
// 	SIGQUIT: value to signal quit (ctrl+\, quite and produce a core dump)
// 	SIG_IGN: value to signal ignore
// 	SIGTSTP: value to signal suspension (ctrl+z, stop and suspend the process)
// ie.
// 	signal(SIGQUIT, SIG_IGN)

// rl_replace_line("", 0)
// 	readline: replace the current line in the input buffer with
// 	"", and 0 for do not refresh.
// rl_done = 1
// 	stop and exit the readline input loop
// rl_on_new_line()
// 	moves the cursor to a new line.
