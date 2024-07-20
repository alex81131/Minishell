/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_counter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:06:51 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/20 20:06:51 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	separator_counter(char *s, size_t i, size_t block)
{
	while (s[i] && s[i] != '\n')
	{
		i += ft_count_whitespace(s + i);
		while (s[i] && !ft_strchr(" \t|<>", s[i]))
			i++;
		if (s[i] && (ft_strchr("|<>", s[i]) || !ft_strncmp(">>", s + i, 2)))
		{
			block++;
			if (!ft_strncmp(">>", s + i, 2))
				i += 2;
			else
				i++;
		}
	}
	return (block);
}
