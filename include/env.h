/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:06:07 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/13 11:50:18 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*id;
	char			*value;
	char			*sum;
	struct s_env	*next;
}	t_env;

void	env_var_add(t_env **head_env, t_env *new);
void	set_env_var(t_env **env, char *id, char *value);
t_env	*env_create(char *env_entry);
t_env	*create_env_list(char **env);
t_env	*get_env_var(t_env *env, char *var);
void	node_free(t_env *node);
void	env_free(t_env *head);
void	print_env(t_env *env);
int		env_lstsize(t_env *env);
t_env	*ps_fetch_var(t_env *env, char *var);


#endif
