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
	if (sh->env && !sh->env->find(sh->env, "PWD"))
	{
		sh->add->new("PWD", getcwd(str, 1024), "string");
		sh->env->add_back(&sh->env, sh->add);
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
		sh->env = sh->hash->new("SHLVL", "1", "string");
	free_string(&n);
}

void	get_env_var(t_sh *sh, char **env, size_t i)
{
	static char	*token[2] = {0};

	sh->hash = ft_hash_initialize();
	if (env[0])
	{
		token[0] = ft_strtok(env[0], "=");
		token[1] = ft_strtok(NULL, "=");
		if (!token[1])
			token[1] = "";
		sh->env = sh->hash->new(token[0], token[1], "string");
		while (env[i])
		{
			token[0] = ft_strtok(env[i], "=");
			token[1] = ft_strtok(NULL, "=");
			if (!token[1])
				token[1] = "";
			sh->add = sh->hash->new(token[0], token[1], "string");
			sh->env->add_back(&sh->env, sh->add);
			i++;
		}
		change_sh_path(sh->env, sh->hash);
	}
	change_shlvl(sh);
	search_pwd(sh);
}

void	replace_env_var(t_sh *sh, char **cmd, size_t i)
{
	size_t	last;
	char	*buff;

	while (cmd[i])
	{
		if (cmd[i][0] == '$')
		{
			buff = ft_strdup(cmd[i]);
			last = ft_arrlen(cmd) - 1;
			free_string(&cmd[i]);
			if (sh->env->search(sh->env, buff + 1))
				cmd[i] = ft_strdup(sh->env->search(sh->env, buff + 1));
			else
			{
				cmd[i] = cmd[last];
				cmd[last] = NULL;
			}
			free(buff);
		}
		i++;
	}
}

/*
search_pwd
	getcwd is in <unistd.h>.
change_shlvl
	shlvl stands for shell level.
replace_env_var				Why need swapping with the end???????
	buff + 1 to copy the rest of the string after "$"
*/