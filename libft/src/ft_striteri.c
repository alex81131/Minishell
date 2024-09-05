/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:26:42 by kyeh              #+#    #+#             */
/*   Updated: 2024/05/17 11:15:51 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
With a return type of void,
you should not return any value, including 0 or NULL.
Hence return ;

Don't need s[i] = '\0' after the loop cuz the length is the same,
with '\0' at the end.

When you call a function through a function pointer,
using either (*f)(...) or f(...) syntax is valid and equivalent.
*/