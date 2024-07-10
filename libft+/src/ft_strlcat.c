/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:03:41 by kyeh              #+#    #+#             */
/*   Updated: 2024/05/14 12:03:41 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len_d;
	size_t	len_s;

	i = 0;
	len_d = ft_strlen(dest);
	len_s = ft_strlen(src);
	if (size <= len_d)
		return (len_s + size);
	while (src[i] && i < size - len_d - 1)
	{
		dest[len_d + i] = src[i];
		i++;
	}
	dest[len_d + i] = '\0';
	return (len_s + len_d);
}
/*
Cut the "size" amount from dest, and then put src as many as we can.
And returns the length of (src + min(dest, size)).
*/
/*
// cc with -lbsd
#include <bsd/string.h>
#include <stdio.h>

int main (void)
{
	char dest[100] = "Why is ";		//word count = 7
	char src[] = "Moulinette the way she is?";//word count = 26
	
	char dest1[] = "Why is ";		//word count = 7
    	printf("%u \n", ft_strlcat(dest, src, 0)); //%i for integer
	printf("%s \n", dest);

	printf("%zu \n", strlcat(dest1, src, 0)); //%i for integer
	printf("%s \n", dest1);
}
*/