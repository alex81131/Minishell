/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:13:16 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/05 19:08:23 by kyeh             ###   ########.fr       */
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
//	ps_expand_utils
ps_get_before_env
ps_get_env_var
ps_get_after_env

#endif
