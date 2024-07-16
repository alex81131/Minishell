/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:07:58 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/10 15:07:58 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_command(void)
{
	size_t	i;

	i = 0;
	while (sh()->cmd[i])
		free_array(sh()->cmd[i++]);
	free(sh()->cmd);
}

void	replace_question_mark(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "$?"))
		{
			free_string(&cmd[i]);
			cmd[i] = ft_itoa(sh()->question_mark);
		}
		i++;
	}
}

void	main_loop(char *buff, size_t i)
{
	char	**arr;
	char	**token;

	token = 0;
	if (analyzer(buff, token, 0))
	{
		arr = ft_split(buff, ';');
		while (arr[i])
		{
			if (!parsing(arr[i]))
			{
				free_array(arr);
				return ;
			}
			if (sh()->redir[0] != 0)
				redirection(0, 0);
			else
				ft_exec(0);
			free_command();
			free_string(&sh()->redir);
			i++;
		}
		free_array(arr);
	}
}

t_sh	*sh(void)
{
	static t_sh	sh = {0};

	return (&sh);
}
