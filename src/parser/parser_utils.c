/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:25:30 by kyeh              #+#    #+#             */
/*   Updated: 2024/09/05 16:26:45 by kyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ps_check_all_null(t_token *token)
{
	int	i;

	i = 1;
	while (token)
	{
		if (token->value)
			i = 0;
		token = token->next;
	}
	return (i);
}
