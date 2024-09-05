/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:03:30 by kyeh              #+#    #+#             */
/*   Updated: 2024/05/14 12:03:30 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while ((char)c != *str)
	{
		if (!*str)
			return (NULL);
		str++;
	}
	return ((char *)str);
}
/*
The function returns char *, so be careful with the return value.
NULL = 0 = a pointer to the value '\0'.
If c = '\0', it won't enter the loop,
	rendering the correct place of the NUL-terminator,
	so in the loop
	if (!*str)	return (0);    is good.
*/