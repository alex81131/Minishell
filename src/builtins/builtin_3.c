/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:14:13 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/13 14:25:07 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_export(t_env *env, t_arg *arg)
{
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
			if (set_env_var(&env, arg->value, eq_sign + 1))
				return (EXIT_FAILURE);
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
		return (EXIT_FAILURE);
	}
	if (print_env(env))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	env_remove(char	*arg, t_env **env)
{
	t_env	*target;
	t_env	*pre_target;

	if (!arg || !env || !*env)
		return ;
	target = *env;
	while (target && ft_strcmp(arg, target->id) != 0)
	{
		pre_target = target;
		target = target->next;
	}
	if (!target)
		return ;
	if (target == *env)
		*env = target->next;
	else
		pre_target->next = target->next;
	node_free(target);
	return ;
}

int	exec_unset(t_env **env, t_arg *arg)
{
	if (!env || !*env)
		return (EXIT_FAILURE);
	while (arg)
	{
		if (ft_strcmp("_", arg->value) != 0 && env_remove(arg->value, env))
			return (1);
		arg = arg->next;
	}
	return (EXIT_SUCCESS);
}
