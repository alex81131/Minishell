/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:07:58 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/10 15:07:58 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh	*sh(void)
{
	static t_sh	sh = {0};

	return (&sh);
}

static void	free_command(void)
{
	size_t	i;

	i = 0;
	while (sh()->cmd[i])
		free_array(sh()->cmd[i++]);
	free(sh()->cmd);
}

static void	replace_question_mark(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "$?"))
		{
			free_string(&cmd[i]);
			cmd[i] = ft_itoa(sh()->question_mark);
		}
		i++;
	}
}

static void	main_loop(char *buff)
{
	char	*token;
	char	**arr;
	size_t	i;

	token = NULL;
	i = 0;
	if (analyzer(buff, token, 0))
	{
		arr = ft_split_minishell(buff);
		while (arr[i])
		{
			if (!parsing(buff))
				return ;
			if (sh()->redir[0])
				redirection(0, 0);
			else
				ft_exec(0);
			free_command();
			free_string(&sh()->redir);
			i++;
		}
		free_array(arr);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*buff;

	(void)ac;
	(void)av;
	print_welcome();
	get_env_var(sh(), env, 1);
	print_prompt(sh()->env);
	signal(SIGQUIT, handle_sigint);
	signal(SIGINT, handle_sigint);
	buff = get_next_line(STDIN_FILENO);
	while (buff)
	{
		main_loop(buff);
		print_prompt(sh()->env);
		free(buff);
		buff = get_next_line(STDIN_FILENO);
	}
	ft_printf_fd(STDOUT_FILENO, "%s\n", "exit");
	if (sh()->path)
		free_array(sh()->path);
	return (EXIT_SUCCESS);
}
/*
main_loop separate the input by unescaped ;
and let parsing parse the |<>
*/