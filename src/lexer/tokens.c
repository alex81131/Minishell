/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:51:59 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/05 19:15:30 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tok_free_one(t_token *token)
{
	if (token->value)
		free(token->value);
	free(token);
}

void	tok_free(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token;
		token = token->next;
		tok_free_one(temp);
	}
}

t_token	*tok_create(char *value, int n, t_token_type type, t_sh *sh)
{
	t_token	*token;
	char	*val;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	val = ft_strndup(value, n);
	if (!val)
	{
		free(token);
		return (NULL);
	}
	token->value = val;
	token->type = type;
	token->sh = sh;
	token->next = NULL;
	return (token);
}

t_token	*tok_last(t_token *token)
{
	while (token->next)
		token = token->next;
	return (token);
}

int	tok_add_back(t_token **head, t_token *new)
{
	if (!new)
		return (1);
	if (!*head)
		*head = new;
	else
		tok_last(*head)->next = new;
	return (0);
}
// void	tok_debug(t_token *token)
// {
// 	char	token_str[12][30];

// 	ft_strlcpy(token_str[INFILE], "INFILE", 30);
// 	ft_strlcpy(token_str[OUTFILE], "OUTFILE", 30);
// 	ft_strlcpy(token_str[HEREDOC], "HEREDOC", 30);
// 	ft_strlcpy(token_str[APPEND], "APPEND", 30);
// 	ft_strlcpy(token_str[PIPE], "PIPE", 30);
// 	ft_strlcpy(token_str[STRING], "STRING", 30);
// 	ft_strlcpy(token_str[SINGLEQUOTE], "SINGLEQUOTE", 30);
// 	ft_strlcpy(token_str[DOUBLEQUOTE], "DOUBLEQUOTE", 30);
// 	ft_strlcpy(token_str[COMMAND], "COMMAND", 30);
// 	ft_strlcpy(token_str[FILENAME], "FILENAME", 30);
// 	ft_strlcpy(token_str[ARGUMENT], "ARGUMENT", 30);
// 	while (token != NULL)
// 	{
// 		printf("(%s) [%s]\n", token_str[token->type], token->value);
// 		token = token->next;
// 	}
// }