/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:44:30 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/16 16:44:30 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hash	*ft_hash_find(t_hash *hash, char *key)
{
	if (hash)
	{
		while (hash)
		{
			if (!ft_strcmp(hash->key, key))
				return (hash);
			hash = hash->next;
		}
	}
	return (NULL);
}
