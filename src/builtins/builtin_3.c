/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:14:13 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/20 14:02:27 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_id(char *id)
{
	int	i;

	if (!*id || (!ft_isalpha(*id) && *id != '_'))
		return (EXIT_FAILURE);
	i = 1;
	while (id[i])
	{
		if (!ft_isalnum(id[i]) && id[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	exec_export(t_env **env, t_arg *arg)
{
	char	*id;
	int		if_err;

	if_err = EXIT_SUCCESS;
	if (!arg)
		if (print_export(*env))
			return (EXIT_FAILURE);
	while (arg)
	{
		id = env_get_id(arg->value);
		if (!id || check_id(id))
		{
			ft_printf_fd(2, "%s: export: %s: not a valid identifier\n",
				PROMPT, id);
			if_err = EXIT_FAILURE;
		}
		else
			if (set_variable(env, arg->value))
				return (free(id), EXIT_FAILURE);
		free(id);
		arg = arg->next;
	}
	return (if_err);
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
		return (EXIT_SUCCESS);
	while (arg)
	{
		if (ft_strcmp("_", arg->value) != 0)
			env_remove(arg->value, env);
		arg = arg->next;
	}
	return (EXIT_SUCCESS);
}
