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

static char	**ft_split_cmd(char *s, size_t n, size_t i, size_t k)
{
	size_t	j;
	char	**entry;

	entry = (char **)malloc(sizeof(char *) * (n + 1));
	if (!entry)
		return (NULL);
	sh()->redir = (char *)ft_calloc(sizeof(char), (n + 1));
	if (!sh()->redir)
		return (NULL);
	while (s[i] && s[i] != '\n')
	{
		i += ft_count_whitespace(s + i);
		j = i;
		while (s[i] && !ft_strchr(";|<>", s[i]) && ft_strncmp(">>", s + i, 2))
			i++;
		if (s[i] && (ft_strchr(";|<>", s[i]) || !ft_strncmp(">>", s + i, 2)))
			entry[k++] = found_redir(s, &i, &j, n);
	}
	i--;
	while (s[i] && ft_strchr(WHITESPACE, s[i]))
		i--;
	entry[k++] = ft_substr(s, j, i - j + 1);
	entry[k] = NULL;
	return (entry);
}

static char	***alloc_command(char str, size_t *n)
{
	char	***cmd;

	*n = separator_counter(str, 0, 0) + 1;
	cmd = (char ***)ft_calloc(*n + 1, sizeof(char **));
	if (!cmd)
		return (NULL);
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
	free_array(entry);
	return (EXIT_SUCCESS);
}

/*
cmd1 'arg1' "arg2 with spaces" | cmd2 < input > output >> append

sh()->cmd[0] = ["cmd1", "arg1", "arg2 with spaces"];
sh()->cmd[1] = ["cmd2", "< input", "> output", ">> append"];
sh()->cmd[2] = NULL;
*/