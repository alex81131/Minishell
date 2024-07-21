/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:23:55 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/20 18:23:55 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_quote(char *str, size_t *i, size_t *j, char *res)
{
	char	quote;

	if (str[*i] == '\'' || str[*i] == '\"')
	{
		quote = str[(*i)++];
		while (str[*i] && str[*i] != quote)
			res[(*j)++] = str[(*i)++];
		if (str[*i] == quote)
			(*i)++;
	}
}

char	*join_quote(char *str, size_t i, size_t j)
{
	char	*res;

	res = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			end_quote(str, &i, &j, res);
		else
			while (str[i] && str[i] != '\'' && str[i] != '\"')
				res[j++] = str[i++];
	}
	free(str);
	return (res);
}
/*
Drastically changed both 2 functions

[Quote Handling]:
Remove quotes while preserving the integrity of the enclosed strings.
*/