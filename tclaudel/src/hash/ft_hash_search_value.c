/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_search_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:41:11 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/16 16:41:11 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_hash_search_value(t_hash *hash, char *key)
{
	while (hash)
	{
		if (!ft_strcmp(hash->key, key))
			return (hash->value);
		hash = hash->next;
	}
	return (NULL);
}
