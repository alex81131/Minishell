/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charpos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:54:50 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/18 19:54:50 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_count_whitespace(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_strchr(WHITE_SPACE, str[i]))
		i++;
	return (i);
}
