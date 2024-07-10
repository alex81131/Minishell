/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:03:21 by kyeh              #+#    #+#             */
/*   Updated: 2024/05/14 12:03:21 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;
	char			sens;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	sens = 1;
	if (dest > src)
	{
		sens = -1;
		d += n - 1;
		s += n - 1;
	}
	while (i < n)
	{
		*d = *s;
		d += sens;
		s += sens;
		i++;
	}
	return (dest);
}
/*
Need to check both positions to decide the direction of copy procedure
	to correctly treat the overlapping situation.
When casting a pointer to another type, the correct syntax is "type *"
Use dummy pointers d and s is simpler to work on pointers and without
	moving the original pointers.
*/