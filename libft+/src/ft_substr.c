/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:41:34 by kyeh              #+#    #+#             */
/*   Updated: 2024/05/14 11:41:34 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	len_s;
	size_t	len_str;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	len_str = 0;
	if (start < len_s)
		len_str = len_s - start;
	if (len_str > len)
		len_str = len;
	str = (char *)malloc((len_str + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s + start, len_str);
	str[len_str] = '\0';
	return (str);
}
/*
ft_strlcpy, copies up to size - 1, ensuring the NUL-termination.
If s or start condition is not legit → empty string;
	if len = 0 → empty string.
*/
/*The following doesn't return an empty string but a NULL,
in case of the starting index >= the length of the string, thus abandoned.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	len_s;
	size_t	len_str;

	len_s = ft_strlen(s);
	if (!s || start >= len_s)
		return (NULL);
	if (len_s - start < len)
		len_str = len_s - start;
	else
		len_str = len;
	str = (char *)malloc((len_str + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s + start, len_str);
	str[len_str] = '\0';
	return (str);
}
*/
/*
len_str = (len_s - start < len) ? len_str = len_s - start : len;
	is a  concise way to write an if-else statement in a single line.
	if (len_s - start < len)
		len_str = len_s - start;
	else
		len_str = len;
*/