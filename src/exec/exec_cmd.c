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

void	exec_builtin(t_sh *sh, size_t j)
{
	char	str[1024];

	if (!ft_strncmp(sh->cmd[j][0], "cd", 3))
		builtin_cd(sh, sh->cmd[j]);
	else if (!ft_strncmp(sh->cmd[j][0], "pwd", 4))
	{
		ft_printf_fd(1, "%s\n", getcwd(str, 1024));
		sh->question_mark = 0;
	}
	else if (!ft_strncmp(sh->cmd[j][0], "env", 4))
		builtin_env(sh, sh->env);
	else if (!ft_strncmp(sh->cmd[j][0], "echo", 5))
		builtin_echo(sh->cmd[j]);
	else if (!ft_strncmp(sh->cmd[j][0], "unset", 5))
		builtin_unset(sh, sh->cmd[j], 0);
	else if (!ft_strncmp(sh->cmd[j][0], "export", 7))
		builtin_export(sh, sh->cmd[j]);
	else if (!ft_strncmp(sh->cmd[j][0], "exit", 5))
	{
		ft_printf_fd(1, "%s\n", "exit\n");
		if (sh->path)
			free_array(sh->path);
		exit(EXIT_SUCCESS);
	}
}

static char	**cpy_env(t_hash *env)
{
	size_t	i;
	char	**env_cpy;

	if (!env)
		return (NULL);
	env_cpy = (char **)malloc((env->len(env) + 1) * sizeof(char *));
	if (!env_cpy)
		return (NULL);
	i = 0;
	while (env)
	{
		env_cpy[i] = ft_strjoin(env->key, "=");
		env_cpy[i] = ft_strjoin_free(env_cpy[i], env->value, 1);
		env = env->next;
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

static void	exec_cmd(t_sh *sh, char **cmd)
{
	size_t	i;
	char	*current_cmd;
	char	**env_cpy;

	i = 0;
	env_cpy = cpy_env(sh->env);

	   // Debugging: Print initial command and env_cpy
    printf("Initial command: %s\n", cmd[0]);

	if (execve(cmd[0], cmd, env_cpy) == -1)
	{

        // Debugging: Check if we reach this point
        printf("execve failed for command: %s\n", cmd[0]);

		current_cmd = ft_strjoin_free("/", cmd[0], 2);

        // Print the current command being tried
        printf("Command: %s\n", current_cmd);

		while (sh->path && sh->path[i])
		{
			cmd[0] = ft_strjoin_free(sh->path[i], current_cmd, 0);
			execve(cmd[0], cmd, env_cpy);
			i++;
			free_string(&cmd[0]);
		}
		if (errno == ENOENT)
			ft_printf_fd(2, "Minishell: %s: Command not found.\n", \
							current_cmd + 1);
		else
			ft_printf_fd(2, "%s\n", strerror(errno));
		free_array(env_cpy);
		free_string(&current_cmd);
		exit(127);
	}
}

static int	ft_fork_process(t_sh *sh, char **cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	signal(SIGQUIT, child_sigint);
	signal(SIGINT, child_sigint);
	pid = fork();
	if (pid == -1)
		ft_printf_fd(2, "%s\n", strerror(errno));
	if (pid == 0)
		exec_cmd(sh, cmd);
	else
	{
		signal(pid, handle_sigint);
		wait(&status);
		if (WIFSIGNALED(status))
			sh->question_mark = WTERMSIG(status + 128);
		else
			sh->question_mark = WEXITSTATUS(status);
		handle_sigint(0);
	}
	signal(SIGQUIT, handle_sigint);
	signal(SIGINT, handle_sigint);
	return (1);
}

void	ft_exec(size_t i)
{
	if (sh()->cmd[i][0] && is_builtin(sh()->cmd[i][0]))
		exec_builtin(sh(), i);
	else if (sh()->cmd[i] && sh()->cmd[i][0])
		ft_fork_process(sh(), sh()->cmd[i]);
	if (sh()->env && sh()->cmd[i] && sh()->cmd[i][0] && sh()->cmd[i][0][0])
		sh()->env->change(sh()->env, "_", \
		sh()->cmd[i][ft_arrlen(sh()->cmd[i]) - 1], "string");
}
/*
exit(127) typically signifies that a command or executable could not be found.
*/