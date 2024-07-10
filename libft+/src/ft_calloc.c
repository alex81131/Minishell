/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:45:00 by kyeh              #+#    #+#             */
/*   Updated: 2024/05/14 11:45:00 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nb, size_t size)
{
	void	*array;

	if (nb > SIZE_MAX || size > SIZE_MAX
		|| (size != 0 && nb > SIZE_MAX / size))
		return (NULL);
	array = (void *)malloc(nb * size);
	if (!array)
		return (0);
	ft_bzero(array, nb * size);
	return (array);
}
/*
Dynamically allocate memory for an array of elements,
initialize them to zero, and then return a pointer to the memory.
*/