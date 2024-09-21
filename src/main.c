/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:49:48 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/21 17:48:31 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_signals = {0};

static void	print_welcome(void)
{
	ft_printf(YELLOW"\n################################################");
	ft_printf("################################\n\n");
	ft_printf(LIGHT_PINK"\n\t\t __  __ ___ _   _ ___ ____  _");
	ft_printf("   _ _____ _     _   \n");
	ft_printf(YELLOW"\t\t|  \\/  |_ _| \\ | |_ _/ ___|| | | | ");
	ft_printf("____| |   | |  \n");
	ft_printf(BLUE"\t\t| |\\/| || ||  \\| || |\\___ \\| |_| |  _");
	ft_printf("| | |   | |  \n");
	ft_printf(GREEN"\t\t| |  | || || |\\  || | ___) |  _  | |___|");
	ft_printf(" |___| |___ \n");
	ft_printf("\033[0;31m""\t\t|_|  |_|___|_| \\_|___|____/|_| |_|__");
	ft_printf("___|_____|_____|\n");
	ft_printf(YELLOW"\n\n\n########################################");
	ft_printf("###############");
	ft_printf("#########################\n\n"RESET);
	ft_printf("\tCreated by\t: kyeh & tkaragoz\n");
	ft_printf("\tGithub\t\t: https://github.com/alex81131/Minishell\n\n\n");
}

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

static int	analyze_line(t_sh *sh, char *input)
{
	t_token	*token;
	int		err;

	token = lexer(sh, input);
	free(input);
	if (!token)
		return (0);
	err = parser(&token);
	if (err)
	{
		tok_free(token);
		if (err == 2)
			return (0);
		return (1);
	}
	if (ms_setup_cmd(sh, &token))
		return (1);
	pre_execution(sh);
	sh_free_token(sh, token);
	return (0);
}

static void	main_loop(t_sh *sh)
{
	char	*input;

	while (1)
	{
		sig_initiate();
		input = readline(PROMPT);
		if (!input)
			break ;
		else if (*input)
		{
			add_history(input);
			if (analyze_line(sh, input))
			{
				ft_printf_fd(STDOUT_FILENO, "Parsing error.\n");
				sh->exit_code = 2;
			}
			input = NULL;
		}
		if (input)
			free(input);
	}
	sh_free_all(sh);
}

int	main(int argc, char **argv, char **env)
{
	t_sh	*sh;

	print_welcome();
	(void)argv[argc];
	sh = init_sh(env);
	if (!sh)
		return (0);
	main_loop(sh);
	ft_printf_fd(STDERR_FILENO, "%s\n", "exit");
	return (EXIT_SUCCESS);
}
