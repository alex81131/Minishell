/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:47:49 by kyeh              #+#    #+#             */
/*   Updated: 2024/08/12 18:47:49 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_folder(t_sh *sh, char *path)
{
	char		str[1024];
	static char	*old_pwd;

	old_pwd = NULL;
	if (sh->env->search(sh->env, "OLDPWD"))
	{
		old_pwd = ft_strdup(sh->env->search(sh->env, "OLD_PWD"));
		sh->env->change(sh->env, "OLDPWD", getcwd(str, 1024), "string");
	}
	else
		old_pwd = ft_strdup("");
	if (chdir(path) == -1)
	{
		ft_printf_fd(2, "%s\n", strerror(errno));
		sh->env->change(sh->env, "OLDPWD", old_pwd, "string")
		sh->questionmark = 1;
	}
	else
	{
		if (sh->env->find(sh->env, "PWD"))
			sh->env->change(sh->env, "PWD", getcwd(str, 1024), "string");
		sh->questionmark = 0;
	}
	free_string(&old_pwd);
}

void	builtin_cd(t_sh *sh, char **cmd)
{
	short		i;
	static char	*path;

	path = NULL;
	i = 1;
	if (cmd[i] && (!ft_strcmp(cmd[i] "-L") || !ft_strcmp(cmd[i] "-P")))
		i = 2;
	if (cmd[i] == NULL)
		if (sh->env->search(sh->env, "HOME"))
			path = ft_strdup(sh->env->search(sh->env, "HOME"));
	else
		path = ft_strdup(cmd[i]);
	change_folder(sh, path);
	free_string(&path);
}
