/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:53:13 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/21 16:53:13 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	grep_operator(char *str, size_t i, size_t n)
{
	static size_t	j;

	if (i == 0)
		j = 0;
	if (!ft_strncmp(">>", str + i, 2))
		sh()->redir[j] = 'd';
	else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		sh()->redir[j] = str[i];
	else
		return ;
	j++;
	if (j >= n)
		j = 0;
	sh()->redir[n] = '\0';
}

char	*operator(char *s, size_t *i, size_t *j, size_t n)
{
	char	*res;
	size_t	end;

	grep_operator(s, *i, n);
	end = *i;
	if (!ft_strncmp(">>", s + *i, 2))
		(*i)++;
	(*i)++;
	while (s[end] && (ft_strchr(" \t\n\v\f\r|<>", s[end])))
		end--;
	res = ft_substr(s, *j, end - *j + 1);
	if (!res)
		free_string(&res);
	*j = *i;
	return (res);
}
/*
grep_redir registers the redirection type.

found_redir returns the string before the redirection and iterates over,
ie.
	*str = cmd1 | cmd2
	*j = 0, *i = 5, end = 3, str[*i] = `|`.
	*j is the starting position and *i the redirection.
	in ft_substr end needs to +1 to copy the correct length (cmd1).
*/