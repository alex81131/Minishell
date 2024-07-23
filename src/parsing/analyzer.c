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

static char	*tokenize(char **ptr_to_str, const char *delimiter)
{
	char	*end;

	if (*ptr_to_str == NULL)
		return (NULL);
	end = *ptr_to_str + ft_sublen(*ptr_to_str, delimiter, 0);
	if (*end)
	{
		*end++ = '\0';
		*ptr_to_str = end;
	}
	else
		*ptr_to_str = NULL;
	return (*ptr_to_str);
}

static int	token_error(char *str, char *token, int i, int j)
{
	if (j == 0)
		ft_printf_fd(2, "minishell: parse error near `%c'\n", \
						token[i]);
	else
		ft_printf_fd(2, "minishell: parse error near `%c%c'\n", \
						token[i], token[j]);
	free_string(&str);
	return (0);
}

static int	condition(char *token, size_t i, char *temp)
{
	if ((ft_strchr("<&|", token[i]) && ft_strchr(">&|", token[i + 1])) || \
		(ft_strchr(">&|", token[i]) && ft_strchr("<&|", token[i + 1])))
		return (token_error(temp, token, i, i + 1));
	if (token[i] == '>' && token[i + 1] == '>' && token[i + 2] == '>')
		return (token_error(temp, token, i, 0));
	return (1);
}

int	analyzer(char *str, char *token, size_t i)
{
	char	*temp;

	temp = ft_strdup(str);
	temp = ft_strclean(temp, " \t", 1);
	token = tokenize(&temp, ";");
	while (token)
	{
		if (token[0])
		{
			i = 0;
			if (ft_strchr("<>&|", token[i]))
				return (token_error(temp, token, i, 0));
			while (token[i + 1])
			{
				if (!condition(token, i, temp))
					return (0);
				i++;
			}
			if (ft_strchr("<>&|", token[i]))
				return (token_error(temp, token, i, 0));
		}
	}
	free_string(&temp);
	return (1);
}
/*
analyzer
	Checks if the tokens are valid.
ft_sublen(const char *s1, const char *s2, int existence)
	Count the characters in s1 that are present/absent in s2.
*/