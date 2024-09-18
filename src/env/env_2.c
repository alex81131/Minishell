/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:27:43 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/18 18:49:49 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	node_free(t_env *node)
{
	free(node->id);
	free(node->value);
	free(node->sum);
	free(node);
}

void	env_free(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		node_free(tmp);
	}
}

int	print_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (EXIT_FAILURE);
	tmp = env;
	while (tmp)
	{
		if (*tmp->value)
			printf("%s\n", tmp->sum);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	env_lstsize(t_env *env)
{
	int		cnt;

	cnt = 0;
	while (env)
	{
		env = env->next;
		cnt++;
	}
	return (cnt);
}

t_env	*get_env_var(t_env *env, char *var)
{
	if (!env || !var)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->id, var))
			return (env);
		env = env->next;
	}
	return (NULL);
}
