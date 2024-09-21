/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:28:32 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/21 17:26:07 by kyeh             ###   ########.fr       */
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

static int	ps_remove_null(t_token **head)
{
	t_token	*temp;
	t_token	*token;

	token = *head;
	while (token && !token->value)
	{
		temp = token;
		token = token->next;
		free(temp);
	}
	*head = token;
	while (token && token->next)
	{
		if (!token->next->value)
		{
			temp = token->next;
			token->next = token->next->next;
			free(temp);
		}
		else
			token = token->next;
	}
	return (0);
}

static int	ps_analyze_redir(t_token *token)
{
	if (token && token->type == PIPE)
		return (1);
	while (token)
	{
		if (token->type == INFILE || token->type == OUTFILE
			|| token->type == HEREDOC || token->type == APPEND)
		{
			if (!token->next || token->next->type != STRING)
				return (1);
			token->next->type = FILENAME;
		}
		else if ((token->type == PIPE && !token->next) \
				|| (token->type == PIPE && token->next->type == PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}

static int	ps_analyze_cmd(t_token *token)
{
	while (token)
	{
		if (token->type == STRING)
		{
			token->type = COMMAND;
			while (token && token->type != PIPE)
			{
				if (token->type == STRING)
					token->type = ARGUMENT;
				token = token->next;
			}
		}
		if (token)
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
	else if (ps_expand_quotes(*token))
		err = 1;
	else if (ps_remove_null(token))
		err = 1;
	else if (ps_check_all_null(*token))
		err = 2;
	else if (ps_analyze_redir(*token))
		err = 1;
	else if (ps_analyze_cmd(*token))
		err = 1;
	else if (ps_analyze_heredoc(*token))
	{
		err = 2;
		ps_unlink_err(*token);
	}
	return (err);
}
// ps_analyze_cmd:
// 	because commands always come before arguments

// ps_remove_null:
// Step 1: Remove leading NULL-value tokens
// Step 2: Remove any NULL-value tokens from the rest of the list

// A linked list can be passed as t_token token, but when manipulating lists,
// 	you have to pass the address &token,
// 	which can make the code more complicated and error-prone.
// Therefore it is cleaner to pass the pointer to the linked list.
// ie.
// 	void remove_first_token(t_token **head)
// 	{
// 		t_token *temp = *head; // Access the current head token
// 		if (temp)
// 		{
// 			*head = temp->next; // Modify the head pointer directly
// 			free(temp); // Free the old head token
// 		}
// 	}

// 	void remove_first_token(t_token *head)
// 	{
// 		t_token **temp = &head; // Now you need to manage this extra pointer
// 		if (*temp)
// 		{
// 			*temp = (*temp)->next; // Accessing the next token
// 			free(*temp); // Free the old head token (but this is tricky)
// 		}
// 	}

// In parser, in order to modify the linked list outside of the function,
// 	**token is needed.
