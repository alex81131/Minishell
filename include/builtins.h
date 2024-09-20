/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:34:37 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/20 13:31:42 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env	t_env;

int	is_builtin(char *name);
int	exec_builtin(t_sh *sh, char *name, t_arg *arg);
int	exec_pwd(void);
int	exec_echo(t_arg *arg);
int	exec_cd(t_env *env, t_arg *arg);
int	exec_export(t_env **env, t_arg *arg);
int	exec_env(t_env *env, t_arg *arg);
int	exec_unset(t_env **env, t_arg *arg);
int	exec_exit(t_sh *sh, t_arg *arg);
int	print_export(t_env *env);

#endif
