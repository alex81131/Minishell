/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:07:04 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/05 16:14:43 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_sh	t_sh;

typedef enum e_token_type
{
	INFILE,
	OUTFILE,
	HEREDOC,
	N_HEREDOC,
	APPEND,
	PIPE,
	STRING,
	SINGLEQUOTE,
	DOUBLEQUOTE,
	COMMAND,
	FILENAME,
	ARGUMENT
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_sh			*sh;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

t_token			*lexer(t_sh *sh, char *line);
int				lex_quote_len(char *str, char quote);
int				lex_get_len(char *str, t_token_type type);
t_token_type	lex_get_type(char *str);

void			tok_free_one(t_token *token);
void			tok_free(t_token *token);
t_token			*tok_create(char *value, int n, t_token_type type, t_sh *sh);
t_token			*tok_last(t_token *token);
int				tok_add_back(t_token **head, t_token *new);
void			tok_debug(t_token *token);

#endif