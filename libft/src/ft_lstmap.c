/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:35:34 by kyeh              #+#    #+#             */
/*   Updated: 2024/05/22 15:47:34 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*node;
	void	*content;

	if (!lst || !f)
		return (NULL);
	new = NULL;
	while (lst)
	{
		content = f(lst->content);
		node = ft_lstnew(content);
		if (!node)
		{
			del(content);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, node);
		lst = lst->next;
	}
	return (new);
}
/*
void *(*f)(void *): declares an f, a function pointer to a function (*f) that:
1. Takes one argument: a void * (pointer to any type).
2. Returns a void * (pointer to any type).

[Comparison]
void (*f)(void *) This means f is a function pointer to a function too, but:
2. Returns nothing (void).

The only difference is that:
void * : returns a pointer to any type,
void   : returns nothing.



The ft_lstadd_back function is designed to handle NULL pointers gracefully.
If the new list is NULL (empty), ft_lstadd_back treats the first addition as 
a special case, effectively initializing the list with the first node.

And since lst is a local variable, any changes you make to lst inside the
function affect only the copy, not the original pointer outside the function.
As long as I don't return (lst), the original lst will stay intact.

The list is NULL-terminated with ft_lstnew.
*/
/*
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*node;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
		return (NULL);
	node = lst;
	while (node->next)
	{
		node = node->next;
		tmp = ft_lstnew(f(node->content));
		if (!tmp)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, tmp);
	}
	return (new_list);
}
*/