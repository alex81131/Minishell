/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:24:21 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/20 17:24:21 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_insert(char *src, char *insert, size_t start, size_t skip)
{
	char	*res;

	res = ft_substr(src, 0, start);
	res = ft_strjoin_free(res, insert, 1);
	res = ft_strjoin_free(res, src + start + skip, 1);
	free(src);
	return (res);
}
/*
USER = alice
echo "Hello, USER! You're home."
	"Hello, alice! You're home."
*/