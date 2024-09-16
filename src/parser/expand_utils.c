/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:10:50 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/16 15:37:05 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ps_name_len(char *var)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[i]) || var[i] == '?' || var[i] == '$')
		return (1);
	while (var[i])
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
			break ;
		i++;
	}
	return (i);
}

static char	*ps_get_env_name(char *var)
{
	int		len;
	char	*name;

	len = ps_name_len(var);
	name = ft_strndup(var, len);
	return (name);
}

char	*ps_get_before_env(char *str, char *var)
{
	int	len;

	len = var - str;
	if (!len)
		return (ft_strdup(""));
	return (ft_strndup(str, len));
}

char	*ps_get_env_var(char *var, t_sh *sh)
{
	char	*name;
	t_env	*env_var;
	int		code;

	name = ps_get_env_name(var);
	if (name && !ft_strcmp(name, "?"))
	{
		free(name);
		if (g_signals.signal_code)
		{
			code = g_signals.signal_code;
			g_signals.signal_code = 0;
			return (ft_itoa(code));
		}
		return (ft_itoa(sh->exit_code));
	}
	else if (name && !ft_strcmp(name, "$"))
		return (free(name), ft_strdup("program_pid"));
	env_var = ps_fetch_var(sh->env, name);
	if (name)
		free(name);
	if (!env_var || !env_var->value)
		return (NULL);
	return (ft_strdup(env_var->value));
}

char	*ps_get_after_env(char *var)
{
	int		len;
	char	*res;

	len = ps_name_len(var);
	res = ft_strdup(var + len);
	return (res);
}

// ps_get_before_env:
// 	var is the position of $ in the string (token->value)
