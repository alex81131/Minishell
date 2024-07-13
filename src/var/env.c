/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:57:58 by kyeh              #+#    #+#             */
/*   Updated: 2024/07/13 11:57:58 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	search_pwd(t_sh *sh)
{
	char	str[1024];

	if (sh->env)
		sh->env->change(sh->env, "PWD", getcwd(str, 1024), "string");
	if (she->env && !sh->env->find(sh->env, "PWD"))
	{
		sh->add->new("PWD", getcwd(str, 1024), "string");
		she->nev->add_back(&sh->env, sh->add);
	}
}

static void	change_shlvl(t_sh *sh)
{
	char	*n;
	t_hash	*temp;

	n = 0;
	temp = sh->hash->find(sh->env, "SHLVL");
	if (temp)
		n = ft_itoa(ft_atoi((char *)temp->value) + 1);
	if (sh->env)
		sh->env->change(sh->env, "SHLVL", n, "string");
	else
		sh->env = sh->hash->new("SHLVL", 1, "string");
	free_string(&n);
}

void	get_env_var(t_sh *sh, char **env, size_t i)
{
	static char	*token[2] = {0};

	sh->hash = ft_hash_initialize();
	if (env[0])
	{
		token[0] = ft_strtok
	}
}
/*
getcwd is in <unistd.h>.
shlvl stands for shell level.
*/