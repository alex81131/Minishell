/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:14:36 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/12 16:13:59 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*lex_strtok(char *str, t_sh *sh)
{
	t_token			*new;
	t_token_type	type;
	int				len;

	new = NULL;
	type = lex_get_type(str);
	len = lex_get_len(str, type);
	new = tok_create(str, len, type, sh);
	return (new);
}

t_token	*lexer(t_sh *sh, char *line)
{
	t_token	*token;
	t_token	*temp;
	int		i;

	i = 0;
	token = NULL;
	while (line[i])
	{
		if (ft_strcmp(WHITESPACE, line + i))
		{
			temp = lex_strtok(&line[i], sh);
			if (!temp)
			{
				tok_free(token);
				return (NULL);
			}
			tok_add_back(&token, temp);
			i += ft_strlen(temp->value);
		}
		else
			i++;
	}
	return (token);
}
// cmd1 < input | cmd2 'arg2' "arg3" >> append

// [token0] STRING:	cmd1
// [token1] INFILE:	<
// [token2] STRING:	input
// [token3] PIPE:		|
// [token4] STRING:	cmd2
// [token5] STRING:	'arg2'
// [token6] STRING:	"arg3"
// [token7] APEND:		>>
// [token8] STRING:	append
