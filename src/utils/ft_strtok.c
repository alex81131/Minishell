/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:27:04 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/17 16:27:04 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_sublen(const char *s1, const char *s2, int existence)
{
	size_t	len;

	len = 0;
	if (existence == 1)
		while (s1[len] && ft_strchr(s2, s1[len]))
			len++;
	if (existence == 0)
		while (s1[len] &&!ft_strchr(s2, s1[len]))
			len++;
	return (len);
}

char	*ft_strtok(char *str, const char *separator)
{
	char		*next;
	static char	*save;

	if (str == NULL)
		str = save;
	if (*str == '\0')
	{
		save = str;
		return (NULL);
	}
	str += ft_sublen(str, separator, 1);
	if (*str == '\0')
	{
		save = str;
		return (NULL);
	}
	next = str + ft_sublen(str, separator, 0);
	if (*next == '\0')
	{
		save = next;
		return (NULL);
	}
	*next = '\0';
	save = next + 1;
	return (str);
}
