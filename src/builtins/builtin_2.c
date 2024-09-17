/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:42:05 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/17 16:58:59 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_printf_fd(STDERR_FILENO, "%s getcwd() error\n", PROMPT);
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

int	exec_echo(t_arg *arg)
{
	int	nl;

	nl = 1;
	while (arg && is_n_flag(arg->value))
	{
		nl = 0;
		arg = arg->next;
	}
	while (arg)
	{
		printf("%s", arg->value);
		if (arg->next)
			printf("%s", " ");
		arg = arg->next;
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
		ft_printf_fd(2, "%s cd: error retrieving current directory\n",
			PROMPT);
		return (EXIT_FAILURE);
	}
	set_env_var(&env, "OLDPWD", old_cwd);
	set_env_var(&env, "PWD", cwd);
	free(cwd);
	free(old_cwd);
	return (EXIT_SUCCESS);
}

int	exec_cd(t_env *env, t_arg *arg)
{
	t_env	*home_env;
	char	*old_cwd;
	char	*new_dir;
	int		size;

	size = arg_lstsize(arg);
	if (size > 1)
		return (ft_printf_fd(2, "%scd: too many arguments\n", PROMPT), 1);
	old_cwd = getcwd(NULL, 0);
	if (!old_cwd)
		return (ft_printf_fd(2, "%s getcwd() error %s\n", PROMPT,
				strerror(errno)), chdir("/"), 1);
	if ((size == 0 || ft_strcmp(arg->value, "--") == 0))
	{
		home_env = get_env_var(env, "HOME");
		if (!home_env || !home_env->value)
			return (free(old_cwd), ft_printf_fd(2,
					"%s cd: HOME not set\n", PROMPT), 1);
		new_dir = home_env->value;
	}
	else
		new_dir = arg->value;
	if (chdir(new_dir) != 0)
		return (free(old_cwd), ft_printf_fd(2, "%s cd\n", PROMPT), 1);
	return (pwd_update(env, old_cwd));
}
