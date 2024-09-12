/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:14:13 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/12 16:01:03 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (EXIT_FAILURE);
	tmp = env;
	while (tmp)
	{
		printf("%s\n", tmp->sum);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	exec_export(t_env *env, t_arg *arg)
{
	int		i;
	char	*eq_sign;

	if (!arg)
		if (print_env(env))
			return (EXIT_FAILURE);
	while (arg)
	{
		eq_sign = ft_strchr(arg->value, '=');
		if (eq_sign)
		{
			*eq_sign = '\0';
			set_env_var(&env, arg->value[i], eq_sign + 1);
			*eq_sign = '=';
		}
		arg = arg->next;
	}
	return (EXIT_SUCCESS);
}

int	exec_env(t_env *env, t_arg *arg)
{
	if (arg)
	{
		printf("env: '%s': No such file or directory\n", arg->value);
		return ;
	}
	print_env(env);
}

int	env_remove(char	*arg, t_env **env)
{
	t_env	*target;
	t_env	*pre_target;

	if (!arg || !env || !*env)
		return (0);
	target = *env;
	while (target && ft_strcmp(arg, target->id) != 0)
	{
		pre_target = target;
		target = target->next;
	}
	if (!target)
		return (0);
	if (target == *env)
		*env = target->next;
	else
		pre_target->next = target->next;
	node_free(target);
	return (1);
}

int	exec_unset(t_cmd *cmd, t_env **env)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (ft_strcmp("_", cmd[i]) != 0 && env_remove(cmd[i], env))
			return (1);
		i++;
	}
	return (0);
}
