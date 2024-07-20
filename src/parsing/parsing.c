/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:48:02 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/17 17:48:02 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_split(char *str, size_t *i, char c)
{
	(*i)++;
	*i += ft_charpos(str + *i, c) + 1;
}

char	**ft_split_cmd(char *s, size_t n, size_t i, size_t k)
{
	size_t	j;
	char	**entry;

	entry = (char **)malloc(sizeof(char *) * (n + 1));
	if (!entry)
		return (NULL);
	sh()->redir = (char *)ft_calloc(sizeof(char), (n + 1));
	if (!sh()->redir)
		return (NULL);
	j = 0;
	while (s[i] && s[i] != '\n')
	{
		i += ft_count_whitespace(s + i);
		if (s[i] && (ft_strchr(";|<>", s[i]) || ft_strcmp(">>", s + i)))
			entry[k++] = found_redir(s, &j, &i, n);
		else
		{
			while (s[i] && !ft_strchr(" \t;|<>", s[i]))
				i++;
			entry[k++] = ft_substr(s, j, i - j);
			j = i;
		}
	}
	entry[k] = ft_substr(s, j, i - j);
	entry[k + 1] = NULL;
	return (entry);
}

char	***alloc_command(char str, size_t *n)
{
	char	***cmd;

	*n = separator_counter(str, 0, 0) + 1;
	cmd = (char ***)ft_calloc(*n + 1, sizeof(char **));
	return (cmd);
}

char	*parsing(char *sep)
{
	size_t	i;
	size_t	n;
	char	*str;
	char	**entry;

	str = ft_strdup(sep);
	str = fill_str_with_var(str, 0, 0, NULL);
	if (quote_error(str))
	{
		free_string(&str);
		return (NULL);
	}
	if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		str = join_quote(str, 0, 0);
	sh()->cmd = alloc_command(str, &n);
	entry = ft_split_cmd(str, n, 0, 0);
	i = 0;
	while (entry[i])
	{
		sh()->cmd[i] = parse(entry[i]);
		i++;
	}
	free(str);
	free(entry);
	return (1);
}

//	quote_split is changed.