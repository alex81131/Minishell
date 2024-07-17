/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:53:48 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/17 16:53:48 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_sh_path(t_hash *env, t_hash *hash)
{
	if (sh()->path)
	free_array(sh()->path);
	if (hash->search(env, "PATH"))
		sh()->path = ft_split(env->search(env, "PATH"), ':');
	else
		sh()->path = ft_calloc(sizeof(char *), 1);
	sh()->question_,ark = 0;
}
