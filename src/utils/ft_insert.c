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

include "minishell.h"

char	*ft_insert(char *src, char *insert, size_t n, size_t len)
{
	char	*res;

	res = ft_substr(src, 0, n);
	res = ft_strjoin_free(res, insert, 1);
	res = ft_strjoin_free(res, src + n + len, 1);
	free(src);
	return (res);
}
