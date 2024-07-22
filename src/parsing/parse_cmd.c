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

static size_t	tail_trim(char *s, size_t i)
{
	size_t	end;

	end = i - 1;
	while (s[end] && ft_strchr(WHITESPACE, s[end]))
		end--;
	end++;
	return (end);
}

static char	**fill_cmd(char **cmd, char *s, size_t i, size_t k)
{
	size_t	j;

	while (s[i])
	{
		i += ft_count_whitespace(s + i);
		j = i;
		while (s[i] && !in_quote(s, i))
			i++;
		if (s[i] && !in_quote(s, i))
			cmd[k++] = ft_substr(s, j, tail_trim(s, i) - j);
		j = ++i;
		while (s[i] && in_quote(s, i))
			i++;
		cmd[k++] = ft_substr(s, j, i - 1 - j);
	}
}

char	**parse(char *str)
{
	size_t	n;
	char	**cmd;

	n = operator_counter(str, 0, 0);
	cmd = (char **)ft_calloc(n + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	cmd = fill_cmd(cmd, str, 0, 0);
	return (cmd);
}
