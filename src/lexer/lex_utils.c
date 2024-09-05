/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:11:55 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/05 19:15:16 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_quote_len(char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

static int	get_meta_char_type(char c)
{
	int	type;

	type = 0;
	if (c == '|')
		type = 1;
	else if (c == '<')
		type = 2;
	else if (c == '>')
		type = 3;
	else if (c == '\"')
		type = 4;
	else if (c == '\'')
		type = 5;
	return (type);
}

static int	lex_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i += lex_quote_len(&(str[i]), '\'');
		else if (str[i] == '\"')
			i += lex_quote_len(&(str[i]), '\"');
		else if (get_meta_char_type(str[i]) || str[i] == WHITESPACE)
			break ;
		i++;
	}
	return (i);
}

int	lex_get_len(char *str, t_token_type type)
{
	int	len;

	len = 0;
	if (type == HEREDOC || type == APPEND)
		len = 2;
	else if (type == INFILE || type == OUTFILE || type == PIPE)
		len = 1;
	else if (type == STRING)
		len = lex_strlen(str);
	return (len);
}

t_token_type	lex_get_type(char *str)
{
	if (str[0] == '<')
	{
		if (str[1] == '<')
			return (HEREDOC);
		else
			return (INFILE);
	}
	else if (str[0] == '>')
	{
		if (str[1] == '>')
			return (APPEND);
		else
			return (OUTFILE);
	}
	else if (str[0] == '|')
		return (PIPE);
	return (STRING);
}
// lex_quote_len stops on the next quote.