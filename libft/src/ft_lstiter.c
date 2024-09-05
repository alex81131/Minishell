/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:07:41 by kyeh              #+#    #+#             */
/*   Updated: 2024/05/17 14:47:22 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*node;

	if (!lst || !f)
		return ;
	node = lst;
	while (node)
	{
		f(node->content);
		node = node->next;
	}
}
/* Or:
void	ft_lstiter(t_list *lst, void (*f)(void *));
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
*/
/*
f(node->content) = (*f)(node->content)
When you use the name of a function pointer in a function call, the language
automatically interprets it as a pointer to a function and applies the
dereference for you. Thus, explicitly dereferencing it with * is not necessary,
but it's not wrong either—it's just redundant.
*/