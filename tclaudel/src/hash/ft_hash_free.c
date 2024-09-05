/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:44:14 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/16 14:44:14 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_hash_free(t_hash **hash)
{
	t_hash	*next;

	if (!hash)
		return ;
	while (*hash)
	{
		next = (*hash)->next;
		ft_hashdel(hash, (*hash)->before, (*hash)->next);
		*hash = next;
	}
}
