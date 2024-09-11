/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:49:48 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/11 15:52:41 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	analyze_line(t_sh *sh, char *input)
{
	t_token	*token;
	int		err;

	token = lexer(sh, input);
	free(input);
	if (!token)
		return (0);
	err = parser(&token);
	if (!err)
	{
		tok_free(token);
		if (err == 2)
			return (0);
		return (1);
	}
	if (ms_setup_exe(sh, &token))
		return (1);
	exe(sh);
	ms_free_token(sh, token);
	return (0);
}

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
	sh->exec = NULL;
	sh->pids = NULL;
	sh->exec_count = 0;
	sh->pid_count = 0;
	sh->exit_code = 0;
	return (sh);
}

static void	main_loop(t_sh *sh)
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		else if (*input)
		{
			add_history(input);
			if (!analyze_line(sh, input))
			{
				ft_printf_fd(STDOUT_FILENO, "Error in handling line\n");
				sh->exit_code = 2;
			}
			//line = NULL;
		}
		if (input)
			free(input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_sh	*sh;

	(void)argv[argc];
	sh = init_sh(env);
	if (!sh)
		return (NULL);
	sig_initiate();
	main_loop(sh);
	ft_printf_fd(STDOUT_FILENO, "%s\n", "exit");
	return (EXIT_SUCCESS);
}
