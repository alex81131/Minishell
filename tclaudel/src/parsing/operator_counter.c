/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_counter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:06:51 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/20 20:06:51 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_escaped(char *s, size_t i)
{
	int	res;

	if (i == 0)
		return (0);
	res = 0;
	while (i > 0 && s[i - 1] == '\\')
	{
		res = !res;
		i--;
	}
	return (res);
}

int	in_quote(char *s, size_t i)
{
	int		in_single_quote;
	int		in_double_quote;
	size_t	j;

	in_single_quote = 0;
	in_double_quote = 0;
	j = 0;
	while (j <= i && s[j] != '\n')
	{
		if (s[j] == '\'' && !if_escaped(s, i) && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (s[j] == '\"' && !if_escaped(s, i) && !in_single_quote)
			in_double_quote = !in_double_quote;
		j++;
	}
	return (in_single_quote || in_double_quote);
}

size_t	operator_counter(char *s, size_t i, size_t block)
{
	while (s[i] && s[i] != '\n')
	{
		if (!in_quote(s, i) && !if_escaped(s, i) && ft_strchr("|<>", s[i]))
		{
			block++;
			if (!ft_strncmp(">>", s + i, 2))
				i++;
			if (!ft_strncmp("<<", s + i, 2))
				i++;
		}
		i++;
	}
	return (block);
}

/*
The logical NOT operator ! can be used with integer types to achieve 
boolean-like behavior, even though int itself is not a boolean type.
	If in_single_quote is 0,
	!in_single_quote evaluates to 1 (true).
*/