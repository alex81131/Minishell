/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:38:15 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/11 14:38:15 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*bld_ini(void)
{
	t_cmd	*res;

	res = (t_cmd *)malloc(sizeof(t_cmd));
	if (!res)
		return (NULL);
	res->arg = NULL;
	res->name = NULL;
	res->fd_in = STDIN_FILENO;
	res->fd_out = STDOUT_FILENO;
	res->redirs = NULL;
	res->next = NULL;
	return (res);
}

void	bld_free(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd)
	{
		temp = cmd;
		if (cmd->name)
			free(cmd->name);
		if (cmd->arg)
			arg_free(cmd->arg);
		if (cmd->redirs)
			fn_free(cmd->redirs);
		cmd = cmd->next;
		free(temp);
	}
}

int	bld_lstsize(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

// void	bld_debug(t_cmd *exe)
// {
// 	t_arg		*arg;
// 	t_filename	*filename;

// 	while (exe)
// 	{
// 		printf(YELLOW "----------- EXE ----------\n");
// 		printf(BLUE);
// 		arg = exe->arg;
// 		filename = exe->redir;
// 		printf("CMD: [%s]\n", exe->cmd);
// 		printf("HEREDOC: [%d]\n", exe->here_doc);
// 		printf("ARG: [%p]\n", exe->arg);
// 		printf("FILENAME: [%p]\n", exe->redir);
// 		if (arg != NULL)
// 			printf("#ARG\n");
// 		printf(RESET);
// 		while (arg != NULL)
// 		{
// 			printf("---->[%s]\n", arg->value);
// 			arg = arg->next;
// 		}
// 		printf(BLUE);
// 		if (filename != NULL)
// 			printf("#REDIR\n");
// 		printf(RESET);
// 		while (filename != NULL)
// 		{
// 			printf("---->[%s]\n", filename->path);
// 			printf("---->[%d]\n", filename->type);
// 			filename = filename->next;
// 		}
// 		printf(BLUE);
// 		printf("NEXT: [%p]\n", exe->next);
// 		if (exe->next == NULL)
// 			printf(YELLOW "-------------------\n" RESET);
// 		exe = exe->next;
// 	}
// }
