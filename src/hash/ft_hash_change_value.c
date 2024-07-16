/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_change_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:52:52 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/16 16:52:52 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_hash_change_value(t_hash *hash, char *key, void *value, char *type)
{
	t_hash	*node;

	node = ft_hash_find(hash, key);
	if (node)
	{
		ft_memdel(&node->value);
		node->value = ft_strdup(value);
		return ;
	}
	else
		hash->add_back(&hash, ft_hashnew(key, value, type));
}
//	Assuming that value is a string