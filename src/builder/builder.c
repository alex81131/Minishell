/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:10:45 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/11 14:10:45 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	bld_redir(t_exe *exe, t_token *token)
{
	t_filename	*temp;

	if (token->next && token->next->value
		&& (token->type == APPEND || token->type == N_HEREDOC
			|| token->type == INFILE || token->type == OUTFILE))
	{
		temp = fn_create(token->next->value, token->type);
		if (!temp)
			return (-1);
		fn_add_back(&exe->redir, temp);
		return (1);
	}
	return (0);
}

static int	bld_arg(t_exe *exe, t_token *token)
{
	t_arg	*new;

	if (token->type == ARGUMENT)
	{
		new = arg_create(token->value);
		if (!new)
			return (-1);
		arg_add_back(&exe->arg, new);
	}
	return (0);
}

t_exe	builder(t_token	*token)
{
	t_exe	*exe;

	exe = bld_ini();
	if (!exe)
		return (NULL);
	while (token)
	{
		if (token->type == PIPE)
		{
			exe->next = builder(token->next);
			break ;
		}
		else if (token->type == COMMAND)
		{
			exe->cmd = ft_strdup(token->value);
			if (!exe->cmd)
				return (NULL);
		}
		bld_redir(exe, token);
		bld_arg(exe, token);
		token = token->next;
	}
	return (exe);
}
