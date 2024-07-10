/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:24:38 by kyeh              #+#    #+#             */
/*   Updated: 2024/05/16 18:49:11 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}
/*
del(lst->content) = (*del)(lst->content)
When you use the name of a function pointer in a function call, the language
automatically interprets it as a pointer to a function and applies the
dereference for you. Thus, explicitly dereferencing it with * is not necessary,
but it's not wrong either—it's just redundant.

So it's like we only write the idea and the logic of deletion,
and we can point to a specific deletion function
depending on different data types.

Imagine you have a toy box (lst) with a toy inside (lst->content)
When it's time to clean up, you need to put the toy back on the shelf
and the toy box back in the closet. free(lst) is like putting the toy box away
in the closet. But before you do that, you need to take care of the toy
inside it.The (*del)(lst->content) part is like taking the toy out of the box
and putting it back on the shelf where it belongs.
*/