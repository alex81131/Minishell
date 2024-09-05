/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:06:56 by kyeh              #+#    #+#             */
/*   Updated: 2024/05/17 14:39:57 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}
/*
Need to check if the list is initially empty (*lst is NULL).
Otherwise it will cause a runtime error.

So ft_lstlast(*lst) is the last node in the linked list, which is also
a pointer, and ft_lstlast(*lst)->next is the pointer "next"
in the pointer list ft_lstlast(*lst)

Remember you didn't put * when writing new->next
*/