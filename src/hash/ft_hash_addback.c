/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_addback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:32:48 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/16 12:32:48 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_hash_addback(t_hash **hash, t_hash *new)
{
	t_hash	*last;

	if (!hash || !new)
		return ;
	if (*hash)
	{
		last = *hash;
		while (last->next)
			last = last->next;
		last->next = new;
		new->top = (*hash)->top;
		new->before = last;
	}
	else
		*hash = new;
}
/*
I changed from new->top = hash;
to new->top = (*hash)->top;
*/