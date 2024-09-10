/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:45:16 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/10 15:12:48 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_final_path(char **paths, char *cmd)
{
	char	*final_path;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		final_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!final_path)
			return (NULL);
		if (access(final_path, X_OK | F_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (NULL);
}

static char	*get_path(char *cmd, t_env *env)
{
	char	*path_value;
	char	**paths;
	char	*final_path;
	int		i;

	if (cmd && !cmd[0])
		return (NULL);
	i = -1;
	while (!env || (cmd[++i]) == '/')
		return (ft_strdup(cmd));
	path_value = get_env_var(env, "PATH")->value;
	if (!path_value)
		return (ft_strdup(cmd));
	paths = ft_split(path_value, ':');
	if (!paths)
		return (ft_strdup(cmd));
	final_path = get_final_path(paths, cmd);
	free_arr(paths);
	return (final_path);

}

static char	**cnv_env_to_arr(t_env *env)
{
	char	**env_arr;
	int		size;
	int		i;

	i = 0;
	size = env_lstsize(env);
	env_arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env_arr)
		return (NULL);
	while (env)
	{
		env_arr[i] = env->sum;
		env = env->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

static char	get_cmd(char *cmd, t_args *args)
{
	int		i;
	int		arg_size;
	char	**final_cmd;

	arg_size = ft_lstsize(args);
	cmd = (char **)malloc(sizeof (arg_size + 2) * (char *));
	if (!cmd)
		return (NULL);
	i = 0;
	final_cmd[i++] = ft_strdup(cmd);
	if (args)
	{
		final_cmd[i] = ft_strdup(args->value);
		args = args->next;
		i++;
	}
	final_cmd[i] = NULL;
	return (final_cmd);
}

int	exec_cmd(t_sh *sh, char *cmd, t_args *args)
{
	char	*path;
	char	**cmd;
	char	**env;

	if (!cmd)
		return (0);
	path = get_path(cmd, sh->env);
	if (!path)
		return (ft_printf_fd("Command path is not found: %s\n",
				strerror(errno)), -1);
	env = cnv_env_to_arr(sh->env);
	if (!env)
		return (free(path), -1);
	cmd = get_cmd(cmd, args);
	if (!cmd)
		return (free(path), free_arr(env), -1);
	if (execve(path, cmd, env) == -1)
	{
		ft_printf_fd("Command is not found: %s\n", strerror(errno));
		return (free(path), free_arr(env), free_cmd(cmd), -2);
	}
	return (free(path), free(env), free_arr(cmd), 0);
}
