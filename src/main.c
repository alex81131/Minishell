/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:49:48 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/12 16:47:14 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_signal = {0};

static int	ms_setup_cmd(t_sh *sh, t_token **token)
{
	sh->cmd = builder(*token);
	tok_free(*token);
	*token = NULL;
	if (!sh->cmd)
		return (1);
	sh->cmd_count = bld_lstsize(sh->cmd);
	sh->pids = (pid_t *)malloc((sh->cmd_count + 1) * sizeof(pid_t));
	if (!sh->pids)
		return (1);
	sh->pid_count = 0;
	return (0);
}

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
	if (ms_setup_cmd(sh, &token))
		return (1);
	pre_execution(sh);
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
	sh->cmd = NULL;
	sh->pids = NULL;
	sh->cmd_count = 0;
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
		return (0);
	sig_initiate();
	main_loop(sh);
	ft_printf_fd(STDOUT_FILENO, "%s\n", "exit");
	return (EXIT_SUCCESS);
}
