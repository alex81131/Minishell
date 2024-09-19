/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:38:16 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/19 17:13:00 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_variable(t_env **env, char *arg_value)
{
	char	*eq_sign;

	eq_sign = ft_strchr(arg_value, '=');
	if (eq_sign)
	{
		*eq_sign = '\0';
		if (set_env_var(env, arg_value, eq_sign + 1))
			return (EXIT_FAILURE);
		*eq_sign = '=';
	}
	else if (set_env_var(env, arg_value, ""))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*env_get_id(char *sum)
{
	char	*eq_sign;

	if (!sum)
		return (NULL);
	eq_sign = ft_strchr(sum, '=');
	if (!eq_sign)
		return (ft_strdup(sum));
	else if (eq_sign - sum == 0)
		return (NULL);
	return (ft_strndup(sum, eq_sign - sum));
}
