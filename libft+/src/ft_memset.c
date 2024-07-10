/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:03:25 by kyeh              #+#    #+#             */
/*   Updated: 2024/05/14 12:03:25 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = ptr;
	while (i < n)
		str[i++] = c;
	return (str);
}
/*
void: the function does not return any value
	  or it doesn't need any specific input data
void *: a special type of pointer that can point to any data type
Any pointer type can be implicitly converted to void *
*/