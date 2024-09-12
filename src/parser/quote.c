/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:21:43 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/12 16:18:31 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ps_get_quote_str(char *str, char c, t_sh *sh)
{
	t_token			*res;
	int				len;
	t_token_type	type;

	len = lex_quote_len(str, c) - 1;
	type = DOUBLEQUOTE;
	if (c == '\'')
		type = SINGLEQUOTE;
	if (len)
		res = tok_create(str + 1, len, type, sh);
	else
		res = tok_create('\0', 1, STRING, sh);
	return (res);
}

static int	ps_unquote_len(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\'' || str[i] == '\"')
			break ;
	return (i);
}

static t_token	*ps_parse_quotes(char *str, t_sh *sh)
{
	int		i;
	t_token	*token;
	t_token	*temp;

	i = 0;
	token = NULL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			temp = ps_get_quote_str(&str[i], str[i], sh);
			i += ft_strlen(temp->value) + 1;
		}
		else
		{
			temp = tok_create(&str[i], ps_unquote_len(&str[i]), STRING, sh);
			i += ft_strlen(temp->value) - 1;
		}
		if (!temp)
			return (NULL);
		tok_add_back(&token, temp);
		i++;
	}
	return (token);
}

static char	*ps_combine_tokens(t_token *token)
{
	char	*value;

	value = NULL;
	while (token)
	{
		if (token->value)
		{
			value = ft_strjoin_free(value, token->value, 1);
			if (!value)
				break ;
		}
		token = token->next;
	}
	return (value);
}

int	ps_expand_quotes(t_token *token)
{
	t_token	*str;

	while (token)
	{
		if (token->type == STRING)
		{
			str = ps_parse_quotes(token->value, token->sh);
			ps_expand_variables(str);
			if (token->value)
				free(token->value);
			token->value = ps_combine_tokens(str);
			tok_free(str);
		}
		token = token->next;
	}
	return (0);
}
// ps_expand_quotes:
// 	1. [ps_parse_quotes] strips quotes, creating a token
// 	2. [ps_combine_tokens] replaces environment variables
// 	3. combine the resulting tokens into one final value
// ie. echo I'm' happy
// 	echo (STRING)
// 	I'm' (STRING)
// 	happy (STRING)
// 	(showing only the 2nd token)
// 	1. I + m
// 	2. Im
// 	3. Im

// ps_parse_quotes:
// 	after ps_get_quote_str,
// 	i += ft_strlen + 1, because the quotes have been ripped off
// 	i += ft_strlen - 1, because:
// 	abc
// 	0123
// 	strlen is 3, but the string stops at i = 2.

// ps_get_quote_str: rips the quotes off of the string
// 	"abc"
// 	01234, length = 4 - 1 = 3
// res = tok_create(str + 1, len, type, sh);
// 	str + 1 to skip the opening quote
