/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_allocator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:18:22 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/21 18:18:22 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	block_counter(char *s, size_t i, size_t block)
{
	char	quote;

	while (s[i])
	{
		i += ft_count_whitespace(s + i);
		if (s[i] && (ft_strchr(s + i, '\'') || ft_strchr(s + i, '\"')))
		{
			quote = s[i++];
			if (quote != '\'' && quote != '\"')
				quote = ' ';
			while (s[i] && s[i] != quote)
				i++;
			if (quote == '\'' || quote == '\"')
				i++;
			block++;
		}
		else
		{
			while (s[i] && s[i] != ' ')
				i++;
			block++;
		}
	}
	return (block);
}

char	**parse(char *str)
{
	size_t	n;
	char	**cmd;

	n = block_counter(str, 0, 0);
	cmd = (char **)ft_calloc(n + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	cmd = fill_cmd(cmd, str, 0, 0);
	return (cmd);
}
