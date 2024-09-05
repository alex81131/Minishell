/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:56:20 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/16 12:56:20 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	be_top(t_hash **hash)
{
	t_hash	*top;

	top = *hash;
	while (*hash)
	{
		(*hash)->top = top;
		*hash = (*hash)->next;
	}
	*hash = top;
}

void			ft_hashdel(t_hash **hash, t_hash *before, t_hash *next)
{
	ft_memdel((void *)&(*hash)->key);
	ft_memdel((void *)&(*hash)->value);
	free(*hash);
	if (before && next)
	{
		*hash = before;
		(*hash)->next = next;
		*hash = next;
		(*hash)->before = before;
		*hash = (*hash)->top;
	}
	else if (before)
	{
		*hash = before;
		(*hash)->next = next;
		*hash = (*hash)->top;
	}
	else if (next)
	{
		*hash = next;
		(*hash)->before = before;
		be_top(hash);
	}
	else if (!next && !before)
		*hash = NULL;
}
/*
It's essential to deallocate the memory and then redirect the dangling
pointer *hash to the new .
*/