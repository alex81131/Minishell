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
	t_hash	*add;
	t_hash	*top;

	top = hash->top;
	while (hash)
	{
		if (!ft_strcmp(hash->key, key))
		{
			ft_memdel((void *)&hash->value);
			hash->value = ft_strdup(value);
			return ;
		}
		hash = hash->next;
	}
	add = ft_hashnew(key, value, type);
	hash = top;
	hash->add_back(&hash, add);
}
//	Assuming that value is a string