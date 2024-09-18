/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:38:16 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/09/18 18:39:30 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
