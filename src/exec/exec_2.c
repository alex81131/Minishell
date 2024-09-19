/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:45:16 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/19 15:20:55 by tkaragoz         ###   ########.fr       */
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
	t_env	*path_env;
	char	**paths;
	char	*final_path;
	int		i;

	if (cmd && !cmd[0])
		return (NULL);
	i = -1;
	while (cmd[++i])
		if (!env || cmd[i] == '/')
			return (ft_strdup(cmd));
	path_env = get_env_var(env, "PATH");
	if (!path_env)
		return (ft_strdup(cmd));
	paths = ft_split(path_env->value, ':');
	if (!paths)
		return (ft_strdup(cmd));
	final_path = get_final_path(paths, cmd);
	free_array(paths);
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
		env_arr[i] = ft_strdup(env->sum);
		env = env->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

static char	**get_cmd(char *cmd, t_arg *arg)
{
	int		i;
	int		arg_size;
	char	**final_cmd;

	arg_size = arg_lstsize(arg);
	final_cmd = (char **)malloc(sizeof(char *) * (arg_size + 2));
	if (!final_cmd)
		return (NULL);
	i = 0;
	final_cmd[i++] = ft_strdup(cmd);
	while (arg)
	{
		final_cmd[i] = ft_strdup(arg->value);
		arg = arg->next;
		i++;
	}
	final_cmd[i] = NULL;
	return (final_cmd);
}

int	exec_cmd(t_sh *sh, char *cmd, t_arg *arg)
{
	char		*path;
	char		**final_cmd;
	char		**env;
	struct stat	path_stat;

	if (!cmd)
		return (0);
	path = get_path(cmd, sh->env);
	if (!path)
		return (ft_printf_fd(STDERR_FILENO, "Command path is not found: %s\n",
				strerror(errno)), -1);
	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return (ft_printf_fd(2, "%s: Is a directory\n", cmd), free(path), -1);
	env = cnv_env_to_arr(sh->env);
	if (!env)
		return (free(path), -1);
	final_cmd = get_cmd(cmd, arg);
	if (!final_cmd)
		return (free(path), free_array(env), -1);
	if (execve(path, final_cmd, env) == -1)
	{
		ft_printf_fd(2, "Command is not found: %s\n", strerror(errno));
		return (free(path), free_array(env), free_array(final_cmd), -2);
	}
	return (free(path), free_array(env), free_array(final_cmd), 0);
}
