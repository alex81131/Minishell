/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:25:18 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/17 14:25:18 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_hash_display(t_hash *hash, char *name)
{
	while (hash)
	{
		ft_printf("%s[%s] = %s\n", name, hash->key, hash->value);
		hash = hash->next;
	}
}
