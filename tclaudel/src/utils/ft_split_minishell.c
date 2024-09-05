/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:07:58 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/23 16:07:58 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	block_number(char *buff)
{
	size_t	i;
	size_t	block;

	i = 0;
	block = 0;
	while (*buff && (*buff == ';' || ft_strchr(WHITESPACE, *buff)))
		buff++;
	while (buff[i])
	{
		if (buff[i] && buff[i] != ';')
			block++;
		while (buff[i] && !(!if_escaped(buff, i) && !in_quote(buff, i) && \
												buff[i] == ';'))
			i++;
		while (buff[i] && (buff[i] == ';' || ft_strchr(WHITESPACE, buff[i])))
			i++;
	}
	return (block);
}

static char	**split_action(char **res, char *buff)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (*buff)
	{
		while (*buff && (*buff == ';' || ft_strchr(WHITESPACE, *buff)))
			buff++;
		if (*buff && *buff != ';')
		{
			i = 0;
			while (*(buff + i) && !(!if_escaped(buff, i) && \
					!in_quote(buff, i) && *(buff + i) == ';'))
				i++;
			res[j++] = ft_substr(buff, 0, i);
			if (!res[j - 1])
			{
				free_array(res);
				return (NULL);
			}
			buff += i;
		}
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split_minishell(char *buff)
{
	char	**res;

	res = (char **)ft_calloc(block_number(buff) + 1, sizeof(char *));
	if (!res)
		return (NULL);
	res = split_action(res, buff);
	return (res);
}
