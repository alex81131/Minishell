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

static void	skip_quote(char *str, size_t *i, char c)
{
	(*i)++;
	*i += ft_charpos(str + *i, c) + 1;
}

static char	***alloc_operator(char str, size_t *m, size_t *n)
{
	char	***cmd;

	*m = separator_counter(str, 0, 0) + 1;
	cmd = (char ***)ft_calloc(*m + 1, sizeof(char **));
	if (!cmd)
		return (NULL);
	*n = operator_counter(str, 0, 0);
	sh()->redir = (char *)ft_calloc(sizeof(char), (*n + 1));
	if (!sh()->redir)
		return (NULL);
	return (cmd);
}

static char	**ft_split_cmd(char *s, size_t m, size_t n, size_t k)
{
	size_t	j;
	char	**entry;
	size_t	i;

	entry = (char **)malloc(sizeof(char *) * (m + 1));
	if (!entry)
		return (NULL);
	i = -1;
	while (s[++i] && s[i] != '\n')
	{
		i += ft_count_whitespace(s + i);
		j = i;
		if (s[i] && !in_quote(s, i) \
					&& !if_escaped(s, i) && ft_strchr("<>", s[i]))
			operator(s, &i, &j, n);
		else if (s[i] && !in_quote(s, i) \
					&& !if_escaped(s, i) && ft_strchr(";|", s[i]))
			entry[k++] = operator(s, &i, &j, n);
	}
	while (s[--i] && ft_strchr(WHITESPACE, s[i]))
		;
	entry[k++] = ft_substr(s, j, i - j + 1);
	entry[k] = NULL;
	return (entry);
}

char	parsing(char *line)
{
	size_t	i;
	size_t	m;
	size_t	n;
	char	*str;
	char	**entry;

	str = ft_strdup(line);
	str = fill_str_with_var(str, 0, 0, NULL);
	if (quote_error(str))
	{
		free_string(&str);
		return (0);
	}
	sh()->cmd = alloc_command(str, &m, &n);
	entry = ft_split_cmd(str, m, n, 0);
	i = -1;
	while (entry[++i])
		sh()->cmd[i] = parse(entry[i]);
	sh()->cmd[n] = NULL;
	free(str);
	free_array(entry);
	return (1);
}

/*
cmd1 'arg1' "arg2 with spaces" | cmd2 < input > output >> append

entry[0] = "cmd1 'arg1' \"arg2 with spaces\""
entry[1] = "cmd2 < input > output >> append"
entry[2] = NULL (null-terminated)

sh()->redir[0] = '|'
sh()->redir[1] = '<'
sh()->redir[2] = '>'
sh()->redir[3] = 'd'

sh()->cmd[0] = ["cmd1", "arg1", "arg2 with spaces"]
sh()->cmd[1] = ["cmd2", "< input", "> output", ">> append"]
sh()->cmd[2] = NULL
*/