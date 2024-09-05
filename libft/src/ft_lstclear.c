/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:30:27 by kyeh              #+#    #+#             */
/*   Updated: 2024/05/17 14:18:42 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;

	if (!lst)
		return ;
	while (*lst)
	{
		node = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = node;
	}
}
/*
Careful with the syntax:	node = (*lst)->next;

Calling ft_lstdelone(*lst, del);,  frees the memory of the current node
pointed to by *lst. The pointer *lst will still exist as a variable,
but what it points to after the call to ft_lstdelone is undefined. 
*/