/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:59:04 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/20 16:59:04 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int option)
{
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	else if (!s2)
		return (s1);
	else if (!s1)
		return (s2);
	res = ft_strjoin(s1, s2);
	if (!res)
		return (NULL);
	if (option == 1)
		free(s1);
	if (option == 2)
		free(s2);
	if (option == 3)
	{
		free(s1);
		free(s2);
	}
	return (res);
}
