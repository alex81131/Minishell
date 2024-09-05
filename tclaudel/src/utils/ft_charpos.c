/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charpos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:03:05 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/20 18:03:05 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_charpos(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

size_t	ft_charrpos(const char *str, int c)
{
	size_t	i;

	i = ft_strlen(str);
	if (c == 0)
		return (i);
	while (i--)
		if (str[i] == c)
			return (i);
	return (0);
}
