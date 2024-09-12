/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:42:05 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/11 18:14:03 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(t_args *args)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_printf_fd(STDERR_FILENO, "%s getcwd() error", PROMPT);
		return (EXIT_FAILURE);
	}
	printf("%s %s\n", PROMPT, cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}

static int	is_n_flag(char *flag)
{
	int	i;

	if (ft_strncmp(flag, "-n", 2))
	{
		return (0);
	}
	i = 2;
	while (flag[i])
	{
		if (flag[i] != 'n')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	exec_echo(t_args *args)
{
	int	nl;

	nl = 1;
	while (args && is_n_flag(args->value))
	{
		nl = 0;
		args = args->next;
	}
	while (args)
	{
		printf("%s", args->value);
		if (args->next)
			printf("%s", " ");
	}
	if (nl)
		printf("%s", "\n");
	return (EXIT_SUCCESS);
}

static int	pwd_update(t_env *env, char *old_cwd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		free(old_cwd);
		ft_printf_fd(STDERR_FILENO, "%s cd: error retrieving current directory",
			PROMPT);
		return (EXIT_FAILURE);
	}
	set_env_var(env, "OLDPWD", old_cwd);
	set_env_var(env, "PWD", cwd);
	free(cwd);
	free(old_cwd);
	return (EXIT_SUCCESS);
}

int	exec_cd(t_env *env, t_args *args)
{
	t_env	*home_env;
	char	*old_cwd;
	char	*new_dir;
	int		size;

	size = arg_listsize(args);
	if (size > 1)
		return (ft_printf_fd(2, "%scd: too many arguments", PROMPT), 1);
	old_cwd = getcwd(NULL, 0);
	if (!old_cwd)
		return (ft_printf_fd(STDERR_FILENO, "%s getcwd() error", PROMPT), 1);
	if ((size == 0 || ft_strcmp(args->value, "--") == 0))
	{
		home_env = get_env_var(env, "HOME");
		if (!home_env || !home_env->value)
			return (free(old_cwd), ft_printf_fd(STDERR_FILENO,
					"%s cd: HOME not set\n", PROMPT), 1);
		new_dir = home_env->value;
		free(home_env);
	}
	else
		new_dir = args->value;
	if (chdir(new_dir) != 0)
		return (free(old_cwd), ft_printf_fd(STDERR_FILENO, "%s cd", PROMPT), 1);
	return (pwd_update(env, old_cwd));
}
