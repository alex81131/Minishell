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

static char	***alloc_operator(char *str, size_t *n)
{
	char	***cmd;

	*n = operator_counter(str, 0, 0) + 1;
	cmd = (char ***)ft_calloc(*n + 1, sizeof(char **));
	if (!cmd)
		return (NULL);
	sh()->redir = (char *)ft_calloc(*n + 1, sizeof(char));
	if (!sh()->redir)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

void	skip_quote_char(char *s, size_t *i, size_t *pos, char *charset)
{
	*i += ft_count_whitespace(s + *i);
	*pos = *i;
	if (s[*i] && s[*i] == '\'')
		skip_quote(s, i, '\'');
	else if (s[*i] && s[*i] == '\"')
		skip_quote(s, i, '\"');
	else if (s[*i] && !ft_strchr(charset, s[*i]))
		while (s[*i] && !ft_strchr(charset, s[*i]))
			(*i)++;
}

static char	**ft_split_cmd(char *s, size_t n, size_t i, size_t k)
{
	size_t	pos;
	char	**entry;

	entry = (char **)malloc(sizeof(char *) * (n + 1));
	if (!entry)
		return (NULL);
	pos = i;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] && !(!if_escaped(s, i) && ft_strchr("|<>", s[i])))
			i++;
		if (s[i] && !if_escaped(s, i) && ft_strchr("|<>", s[i]))
			entry[k++] = operator(s, &i, &pos, n);
	}
	while (s[--i] && ft_strchr(WHITESPACE, s[i]))
		;
	entry[k++] = ft_substr(s, pos, i - pos + 1);
	if (!entry[k - 1])
	{
		free_array(entry);
		entry = NULL;
		return (NULL);
	}
	entry[k] = NULL;
	return (entry);
}

static int	parsing_setup(char *line, char **str, size_t *n)
{
	*str = ft_strdup(line);
	if (!*str)
		return (0);
	*str = fill_str_with_var(*str, 0, 0);
	if (!*str || quote_error(*str))
	{
		free(*str);
		return (0);
	}
	sh()->cmd = alloc_operator(*str, n);
	if (!sh()->cmd)
	{
		free(*str);
		return (0);
	}
	return (1);
}

char	parsing(char *line)
{
	size_t	i;
	size_t	n;
	char	*str;
	char	**entry;

	if (!parsing_setup(line, &str, &n))
		return (0);
	entry = ft_split_cmd(str, n, 0, 0);
	if (!entry)
	{
		free(str);
		free(sh()->cmd);
		return (0);
	}
	i = 0;
	while (entry[i])
	{
		sh()->cmd[i] = parse(entry[i]);
		i++;
	}
	sh()->cmd[i] = NULL;
	free(entry);
	free(str);
	return (1);
}

/*
cmd1 < input | cmd2 'arg2' "arg3" >> append

entry[0] = "cmd1"
entry[1] = "input"
entry[2] = "cmd2 'arg2' "arg3""
entry[3] = "append"
entry[4] = NULL (null-terminated)

sh()->redir[0] = '<'
sh()->redir[1] = '|'
sh()->redir[2] = '>>'
sh()->redir[3] = NULL

sh()->cmd[0] = ["cmd1"]
sh()->cmd[1] = ["input"]
sh()->cmd[2] = ["cmd2", "arg2", "arg3"]
sh()->cmd[3] = ["append"]
sh()->cmd[4] = NULL
*/