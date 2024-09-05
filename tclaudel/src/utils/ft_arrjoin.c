/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:16:15 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/23 10:16:15 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_arrjoin(char **a1, char **a2)
{
	size_t	i;
	size_t	j;
	char	**res;

	i = 0;
	j = 0;
	res = (char **)malloc((ft_arrlen(a1) + ft_arrlen(a2) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (a1[j])
		res[i++] = ft_strdup(a1[j++]);
	j = 0;
	while (a2[j])
		res[i++] = ft_strdup(a2[j++]);
	res[i] = NULL;
	return (res);
}
