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
	while (s[i])
	{
		i += ft_count_whitespace(s + i);
		if (s[i] && !if_escaped(s, i) && (s[i] == '\'' || s[i] == '\"'))
		{
			skip_quote(s, &i, s[i]);
			block++;
		}
		else
		{
			while (s[i] && !ft_strchr(WHITESPACE, s[i]) && \
					!(!if_escaped(s, i) && (s[i] == '\'' || s[i] == '\"')))
				i++;
			block++;
		}
	}
	return (block);
}

static char	**fill_cmd(char **cmd, char *s, size_t i, size_t k)
{
	size_t	j;

	while (s[i])
	{
		i += ft_count_whitespace(s + i);
		j = i;
		while (s[i] && !ft_strchr(WHITESPACE, s[i]) && !in_quote(s, i))
			i++;
		if (s[i] && in_quote(s, i))
		{
			j = i + 1;
			skip_quote(s, &i, s[i]);
			cmd[k++] = ft_substr(s, j, i - j - 1);
		}
		else
			cmd[k++] = ft_substr(s, j, i - j);
	}
	return (cmd);
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
	free(str);
	return (cmd);
}
