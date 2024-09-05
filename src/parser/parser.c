/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:28:32 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/05 18:06:29 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ps_analyze_quote(t_token *token)
{
	int		i;
	char	*str;

	while (token)
	{
		if (token->type == STRING)
		{
			i = 0;
			str = token->value;
			while (str[i])
			{
				if (str[i] == '\'' || str[i] == '\"')
				{
					i += lex_quote_len(&str[i], str[i]);
					if (!str[i])
						return (1);
				}
				i++;
			}
		}
		token = token->next;
	}
	return (0);
}

int	parser(t_token **token)
{
	int	err;

	err = 0;
	if (ps_analyze_quote(*token))
		err = 1;
	else if (ps_expand_quote(*token))
		err = 1;
	else if (ps_remove_null(*token))
		err = 1;
	else if (ps_check_all_null(*token))
		err = 1;
	else if (ps_handle_redir(*token))
		err = 1;
	else if (ps_handle_cmd(*token))
		err = 1;
	else if (ps_handle_heredoc(*token))
	{
		err = 2;
		ps_unlink_err(*token);
	}
	return (err);
}
