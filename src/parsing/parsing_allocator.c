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

char	*complete_cmd(char *str, char c)
{
	char	*res;
	char	buff[1024];
	int		n;

	res = ft_strdup("\n");
	ft_printf(YELLOW_BOLD"> "RESET);
	while (1)
	{
		n = read(0, buff, 1023);
		buff[n] = '\0';
		res = ft_strjoin_free(res, buff, 1);
		if (ft_strchr(res, c))
			break ;
		if (buff[0])
			ft_printf(YELLOW_BOLD"> "RESET);
	}
	str = ft_strjoin_free(s, res, 3);
	return (str);
}

static size_t	block_counter(char *str, size_t i, size_t block)
{
	char	quote;

	while (str[i])
	{
		i += ft_count_whitespace(str + i);
		if (str[i])
			block++;
		while (str[i] && !ft_strchr(WHITESPACE, str[i]))
			i++;
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
	cmd = fill_cmd(str, cmd, 0, 0);
	return (cmd);
}
