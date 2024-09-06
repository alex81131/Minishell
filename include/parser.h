/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:13:16 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/06 17:11:51 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int		parser(t_token **token);
int		ps_check_all_null(t_token *token);
//	Quotes
int		ps_expand_quotes(t_token *token);
//	Expansion
int		ps_expand_variables(t_token *token);
char	*ps_get_before_env(char *str, char *var);
char	*ps_get_env_var(char *var, t_sh *sh);
char	*ps_get_after_env(char *var);
//	here_doc
int		ps_analyze_heredoc(t_token *token);
void	ps_unlink_err(t_token *token);

#endif
