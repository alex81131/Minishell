/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:00:38 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/05 16:08:05 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_strndup(const char *str, int n)
{
	char	*res;
	int		i;
	int		len;

	i = 0;
	if (!str || n < 0)
		return (NULL);
	if (ft_strlen(str) <= n)
		len = ft_strlen(str);
	else
		len = n;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (str[i] && i < n)
		res[i] = str[i++];
	res[i] = '\0';
	return (res);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	*src = "Source";
	char	*dup_t;
	char	*dup_r;

	dup_t = ft_strdup(src);
	if (!dup_t)
		return (0);
	dup_r = strdup(src);
	if (!dup_r)
		return (0);
	printf("Duplicate test: %s\n", dup_t);
	printf("Duplicate real: %s\n", dup_r);
	free(dup_t);
	free(dup_r);
	return (0);
}*/