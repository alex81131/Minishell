/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:15:31 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/05 18:21:05 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_list(char **env)
{
	int		i;
	t_env	*new;
	t_env	*env_list;

	env_list = NULL;
	if (!env || !*env)
		return (env_create("_=/usr/bin/env"));
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
