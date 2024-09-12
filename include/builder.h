/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:11:56 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/11 14:11:56 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_H
# define BUILDER_H

//	t_cmd
t_cmd		*builder(t_token *token);
t_cmd		*bld_ini(void);

void		bld_free(t_cmd *exe);
int			bld_lstsize(t_cmd *exe);
void		bld_debug(t_cmd *exe);

//	t_filename
t_filename	*fn_create(char *name, t_token_type type);
t_filename	*fn_last(t_filename *filename);
int			fn_add_back(t_filename **head, t_filename *new);
int			fn_lstsize(t_filename *filename);
void		fn_free(t_filename *filename);

//	t_arg
t_arg		*arg_create(char *value);
t_arg		*arg_last(t_arg *arg);
int			arg_add_back(t_arg **head, t_arg *new);
int			arg_lstsize(t_arg *arg);
void		arg_free(t_arg *arg);

#endif
