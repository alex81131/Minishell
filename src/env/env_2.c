/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:27:43 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/06 17:43:11 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	node_free(t_env *node)
{
	free(node->id);
	free(node->value);
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
