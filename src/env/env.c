/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:15:31 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/17 19:58:27 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_var_add(t_env **head_env, t_env *new)
{
	t_env	*tmp;

	if (!*head_env)
		*head_env = new;
	else
	{
		tmp = (*head_env);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	set_env_var_2(t_env **env, char *id, char *new_value, char *tmp)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (EXIT_FAILURE);
	new->id = ft_strdup(id);
	if (!new->id)
		return (free(new), EXIT_FAILURE);
	new->value = new_value;
	new->sum = tmp;
	new->next = NULL;
	env_var_add(env, new);
	return (EXIT_SUCCESS);
}

int	set_env_var(t_env **env, char *id, char *value)
{
	t_env	*var;
	char	*new_value;
	char	*tmp;

	new_value = ft_strdup(value);
	if (!new_value)
		return (EXIT_FAILURE);
	tmp = ft_strjoin(id, "=");
	if (!tmp)
		return (free(new_value), EXIT_FAILURE);
	tmp = ps_strjoin(tmp, value);
	if (!tmp)
		return (free(new_value), EXIT_FAILURE);
	var = get_env_var(*env, id);
	if (var)
	{
		free(var->value);
		var->value = new_value;
		free(var->sum);
		var->sum = tmp;
	}
	else
		if (set_env_var_2(env, id, new_value, tmp))
			return (free(new_value), free(tmp), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_env	*env_create(char *env_entry)
{
	t_env	*new_env;
	char	*eq_sign;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	eq_sign = ft_strchr(env_entry, '=');
	if (!eq_sign)
	{
		free(new_env);
		return (NULL);
	}
	new_env->sum = ft_strdup(env_entry);
	if (!new_env->sum)
		return (NULL);
	new_env->id = ft_strndup(env_entry, eq_sign - env_entry);
	if (!new_env->id)
		return (NULL);
	new_env->value = ft_strdup(eq_sign + 1);
	if (!new_env->value)
		return (NULL);
	new_env->next = NULL;
	return (new_env);
}

t_env	*create_env_list(char **env)
{
	int		i;
	t_env	*new;
	t_env	*env_list;

	env_list = NULL;
	if (!env || !*env)
		return (env_create("Minishell=Minishell"));
	i = 0;
	while (env[i])
	{
		new = env_create(env[i]);
		if (!new)
			return (NULL);
		env_var_add(&env_list, new);
		i++;
	}
	return (env_list);
}
