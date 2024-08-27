/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:32:53 by kyeh              #+#    #+#             */
/*   Updated: 2024/08/12 19:32:53 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	builtin_export_empty(t_sh *sh, t_hash **env)
{
	t_hash	*top;
	t_hash	*top_cpy;
	t_hash	*cpy;
	t_hash	*add_cpy;

	top = *env;
	cpy = sh->hash->new((*env)->key, (*env)->value, "string");
	*env = (*env)->next;
	while (*env)
	{
		add_cpy = sh->hash->new((*env)->key, (*env)->value, "string");
		cpy->add_back(&cpy, add_cpy);
		*env = (*env)->next;
	}
	cpy->sort_key(&cpy);
	top_cpy = cpy;
	while (cpy)
	{
		if (!ft_strcmp(cpy->key, "-"))
			ft_printf_fd(1, "Declare -x %s=\"%s\"\n", cpy->key, cpy->value);
		cpy = cpy->next;
	}
	cpy = top_cpy;
	cpy->del_all(&cpy);
	*env = top;
}

static char	is_valid_key(char *key)
{
	size_t	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '_' || ft_isalpha(key[i]))
			i++;
		else
			break ;
	}
	return (key[i] == 0);
}

static void	add_key(t_sh *sh, char **key, size_t j, char **token)
{
	while (key[++j])
	{
		token[0] = ft_strtok(key[0], "=");
		token[1] = ft_strtok(NULL, "=");
		if (!is_valid_key(token[0]))
		{
			ft_printf_fd(2, "Minishell: export: `%s':\
						not a valid indentifier\n", token[0]);
			continue ;
		}
		if (!token[1])
			token[1] = "";
		if (token[0][0] && sh->hash->search(sh->env, token[0]))
		{
			sh->env->change(sh->env, token[0], token[1], "string");
			continue ;
		}
		if (ft_strchr(key[j], '='))
			continue ;
		sh->add = sh->hash->new(token[0], token[1], "string");
		if (sh->env)
			sh->env->add_back(&sh->env, sh->add);
		else
			sh->env = sh->hash->new(token[0], token[1], "string");
	}
}

void	builtin_export(t_sh *sh, char **key)
{
	static char	*token[2] = {0};

	if (!key[1] && sh->env)
		builtin_export_empty(sh, &sh->env);
	add_key(sh, key, 0, token);
	sh->question_mark = 0;
	change_sh_path(sh->env, sh->hash);
}
/*
The builtin_export_empty function handles the export command without arguments
by copying the environment variables, sorting them, printing them in the
declare -x key="value" format, and then cleaning up.
*/