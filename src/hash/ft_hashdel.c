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

void	ft_hashdel(t_hash **hash)
{
	if (!*hash)
		return ;
	ft_memdel((void *)&(*hash)->key);
	ft_memdel((void *)&(*hash)->value);
	if ((*hash)->before && (*hash)->next)
	{
		(*hash)->before->next = (*hash)->next;
		(*hash)->next->before = (*hash)->before;
		*hash = (*hash)->top;
	}
	else if ((*hash)->before)
	{
		(*hash)->before->next = NULL;
		*hash = (*hash)->top;
	}
	else if ((*hash)->next)
	{
		(*hash)->next->before = NULL;
		be_top(&(*hash)->next);
	}
	else
		*hash = NULL;
}
/*
Check if 	*hash = (*hash)->top;
	is necessary?

It's essential to deallocate the memory and then redirect the dangling
pointer *hash to the new .
*/