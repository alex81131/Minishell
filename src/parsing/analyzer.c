/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:40:29 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/12 15:40:29 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_error(char *token, int i, int j)
{
	if (j == 0)
		ft_printf_fd(2, "Minishell: parse error near '%c'\n", \
						token[i]);
	else
		ft_printf_fd(2, "Minishell: parse error near '%c%c'\n", \
						token[i], token[j]);
	free_string(&token);
	return (0);
}

static int	condition(char *token, size_t i)
{
	if ((ft_strchr("<&|", token[i]) && ft_strchr(">&|", token[i + 1])) || \
		(ft_strchr(">&|", token[i]) && ft_strchr("<&|", token[i + 1])))
		return (token_error(token, i, i + 1));
	if (token[i] == '>' && token[i + 1] == '>' && token[i + 2] == '>')
		return (token_error(token, i, 0));
	return (1);
}

int	analyzer(char *str, size_t i)
{
	char	*token;

	token = ft_strclean(str, "\t\n\v\f\r", 0);
		if (token[0])
		{
			i = 0;
			if (ft_strchr("<>&|", token[i]))
				return (token_error(token, i, 0));
			while (token[i + 1])
			{
				if (!condition(token, i))
					return (0);
				i++;
			}
			if (ft_strchr("<>&|", token[i]))
				return (token_error(token, i, 0));
		}
	free(token);
	return (1);
}
/*
analyzer
	Checks if the tokens are valid.
ft_sublen(const char *s1, const char *s2, int existence)
	Count the characters in s1 that are present/absent in s2.
*/