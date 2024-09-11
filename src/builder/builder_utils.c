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

t_exe	*bld_ini(void)
{
	t_exe	*res;

	res = (t_exe *)malloc(sizeof(t_exe));
	if (!res)
		return (NULL);
	res->arg = NULL;
	res->cmd = NULL;
	res->fd_in = STDIN_FILENO;
	res->fd_out = STDOUT_FILENO;
	res->redir = NULL;
	res->next = NULL;
	return (res);
}

void	bld_free(t_exe *exe)
{
	t_exe	*temp;

	while (exe)
	{
		temp = exe;
		if (exe->cmd)
			free(exe->cmd);
		if (exe->arg)
			arg_free(exe->arg);
		if (exe->redir)
			fn_free(exe->redir);
		exe = exe->next;
		free(temp);
	}
}

int	bld_lstsize(t_exe *exe)
{
	int	i;

	i = 0;
	while (exe)
	{
		i++;
		exe = exe->next;
	}
	return (i);
}

// void	bld_debug(t_exe *exe)
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
